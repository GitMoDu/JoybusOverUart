// GameCubeControllerReadTask.h

#ifndef _GAMECUBE_CONTROLLER_READ_TASK_h
#define _GAMECUBE_CONTROLLER_READ_TASK_h

#define _TASK_OO_CALLBACKS
#include <TaskSchedulerDeclarations.h>

#include <GameCubeOverUart.h>

class GameCubeControllerReadTask : private Task
{
private:
	enum class ReadStateEnum : uint8_t
	{
		SearchWakeUp = 0,
		WakeUpCheck = 1,
		SearchPolling = 2,
		SearchRead = 3,
		PollRead = 4,
		SynchronizePoll = 5,
		PollRetry = 6
	};

private:
	static constexpr uint32_t DisconnectTimeoutMicros = 50000;
	static constexpr uint32_t ReadTimeoutMicros = 5000;
	static constexpr uint8_t SearchPeriodMillis = 20;

private:
	GameCubeOverUart JoyBusGC;
	GameCubeController::state_data_t& ControllerState;
	const uint32_t UpdatePeriodMicros;

private:
	uint32_t LastRead = 0;
	ReadStateEnum ReadState = ReadStateEnum::SearchWakeUp;

public:
	GameCubeControllerReadTask(Scheduler* scheduler,
		GameCubeController::state_data_t& controllerState,
		HardwareSerial* serialInstance,
		const uint32_t updatePeriodMicros = 10000)
		: Task(TASK_IMMEDIATE, TASK_FOREVER, scheduler, false)
		, JoyBusGC(serialInstance)
		, ControllerState(controllerState)
		, UpdatePeriodMicros(updatePeriodMicros)
	{
	}

	void Start()
	{
		if (!Task::isEnabled())
		{
			Task::enableDelayed(0);
			JoyBusGC.Start();
			ControllerState.Clear();
			ReadState = ReadStateEnum::SearchWakeUp;
		}
	}

	void Stop()
	{
		ControllerState.Clear();
		Task::disable();
		JoyBusGC.Stop();
	}

	bool Callback()
	{
		switch (ReadState)
		{
		case ReadStateEnum::SearchWakeUp:
			JoyBusGC.Poll();
			ControllerState.Clear();
			ReadState = ReadStateEnum::WakeUpCheck;
			Task::delay(SearchPeriodMillis);
			break;
		case ReadStateEnum::WakeUpCheck:
			if (JoyBusGC.ReadControllerData(ControllerState))
			{
				LastRead = micros();
				ReadState = ReadStateEnum::SearchPolling;
				Task::delay(0);
			}
			else
			{
				ReadState = ReadStateEnum::SearchWakeUp;
				Task::delay(SearchPeriodMillis);
			}
			break;
		case ReadStateEnum::SearchPolling:
			JoyBusGC.Poll();
			ControllerState.Clear();
			ReadState = ReadStateEnum::SearchRead;
			Task::delay(SearchPeriodMillis);
			break;
		case ReadStateEnum::SearchRead:
			if (JoyBusGC.ReadControllerData(ControllerState))
			{
				LastRead = micros();
				ControllerState.Connected = true;
				ReadState = ReadStateEnum::SynchronizePoll;
				Task::delay(0);
			}
			else
			{
				ReadState = ReadStateEnum::SearchPolling;
				Task::delay(SearchPeriodMillis);
			}
			break;
		case ReadStateEnum::PollRead:
			if (JoyBusGC.ReadControllerData(ControllerState))
			{
				LastRead = micros();
				ControllerState.Connected = true;
				ReadState = ReadStateEnum::SynchronizePoll;
				Task::delay(0);
			}
			else if (micros() - LastRead > ReadTimeoutMicros)
			{
				ReadState = ReadStateEnum::PollRetry;
				Task::delay(0);
			}
			else
			{
				Task::delay(0);
			}
			break;
		case ReadStateEnum::PollRetry:
			if (micros() - LastRead > DisconnectTimeoutMicros)
			{
				ReadState = ReadStateEnum::SearchPolling;
				Task::delay(0);
			}
			else
			{
				JoyBusGC.Poll();
				ReadState = ReadStateEnum::PollRead;
				Task::delay(SearchPeriodMillis);
			}
			break;
		case ReadStateEnum::SynchronizePoll:
			if (Synchronize())
			{
				JoyBusGC.Poll();
				ReadState = ReadStateEnum::PollRead;
				Task::delay(0);
			}
			break;
		default:
			break;
		}

		return true;
	}

private:
	const bool Synchronize()
	{
		const uint32_t elapsed = micros() - LastRead;

		if (elapsed >= UpdatePeriodMicros)
		{
			return true;
		}
		else if (elapsed + 1001 < UpdatePeriodMicros)
		{
			Task::delay((UpdatePeriodMicros - elapsed - 1001) / 1000);
		}
		else
		{
			Task::delay(0);
		}

		return false;
	}
};

#endif