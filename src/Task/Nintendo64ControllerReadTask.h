// Nintendo64ControllerReadTask.h

#ifndef _NINTENDO_64_CONTROLLER_READ_TASK_h
#define _NINTENDO_64_CONTROLLER_READ_TASK_h

#define _TASK_OO_CALLBACKS
#include <TaskSchedulerDeclarations.h>

#include <Nintendo64OverUart.h>

class Nintendo64ControllerReadTask : private Task
{
private:
	enum class ReadStateEnum : uint8_t
	{
		SearchPolling = 0,
		SearchRead = 1,
		PollRead = 2,
		SynchronizePoll = 3,
		PollRetry = 4
	};

private:
	static constexpr uint32_t DisconnectTimeoutMicros = 50000;
	static constexpr uint32_t ReadTimeoutMicros = 5000;
	static constexpr uint8_t SearchPeriodMillis = 20;

private:
	Nintendo64OverUart JoyBusN64;
	Nintendo64Controller::state_data_t& ControllerState;
	const uint32_t UpdatePeriodMicros;

private:
	uint32_t LastRead = 0;
	ReadStateEnum ReadState = ReadStateEnum::SearchPolling;

public:
	Nintendo64ControllerReadTask(Scheduler* scheduler,
		Nintendo64Controller::state_data_t& controllerState,
		HardwareSerial* serialInstance,
		const uint32_t updatePeriodMicros = 10000)
		: Task(TASK_IMMEDIATE, TASK_FOREVER, scheduler, false)
		, JoyBusN64(serialInstance)
		, ControllerState(controllerState)
		, UpdatePeriodMicros(updatePeriodMicros)
	{
	}

	const bool ControllerPresent()
	{
		return (uint8_t)ReadState >= (uint8_t)ReadStateEnum::PollRead;
	}

	void Start()
	{
		if (!Task::isEnabled())
		{
			Task::enableDelayed(0);
			JoyBusN64.Start();
			ControllerState.Clear();
			ReadState = ReadStateEnum::SearchPolling;
		}
	}

	void Stop()
	{
		ControllerState.Clear();
		Task::disable();
#if !defined(USE_MOCK_CONTROLLER)
		JoyBusN64.Stop();
#endif
	}

	bool Callback()
	{
		switch (ReadState)
		{
		case ReadStateEnum::SearchPolling:
			JoyBusN64.Poll();
			ControllerState.Clear();
			ReadState = ReadStateEnum::SearchRead;
			Task::delay(SearchPeriodMillis);
			break;
		case ReadStateEnum::SearchRead:
			if (JoyBusN64.ReadControllerData(ControllerState))
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
			if (JoyBusN64.ReadControllerData(ControllerState))
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
				JoyBusN64.Poll();
				ReadState = ReadStateEnum::PollRead;
				Task::delay(SearchPeriodMillis);
			}
			break;
		case ReadStateEnum::SynchronizePoll:
			if (Synchronize())
			{
				JoyBusN64.Poll();
				ReadState = ReadStateEnum::PollRead;
				Task::delay(0);
			}
			break;
		default:
			break;
		}

		return true;
	}

	const bool Synchronize()
	{
		const uint32_t elapsed = micros() - LastRead;

		if (elapsed >= UpdatePeriodMicros)
		{
			return true;
		}
		else if (elapsed + 1001 < UpdatePeriodMicros)
		{
			Task::delay(1);
		}
		else
		{
			Task::delay(0);
		}

		return false;
	}
};

#endif

