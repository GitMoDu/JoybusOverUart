// GCControllerLogTask.h

#ifndef _GC_CONTROLLER_LOG_TASK_h
#define _GC_CONTROLLER_LOG_TASK_h

#define _TASK_OO_CALLBACKS
#include <TaskSchedulerDeclarations.h>

#include <GameCubeController.h>

class GCControllerLogTask : private Task
{
private:
	GameCubeController::state_data_t& ControllerState;

	const uint32_t UpdatePeriodMicros = 0;

	bool LastControllerState = true;

public:
	GCControllerLogTask(Scheduler* scheduler,
		GameCubeController::state_data_t& controllerState,
		const uint32_t updatePeriodMicros = 333000)
		: Task(TASK_IMMEDIATE, TASK_FOREVER, scheduler, true)
		, ControllerState(controllerState)
		, UpdatePeriodMicros(updatePeriodMicros)
	{
	}

	bool Callback()
	{
		if (LastControllerState != ControllerState.Connected)
		{
			LastControllerState = ControllerState.Connected;

			if (ControllerState.Connected)
			{
				Serial.println(F("Found controller!"));
			}
			else
			{
				Serial.println(F("No controller."));
			}
		}

		if (ControllerState.Connected)
		{
			Serial.print(F("Buttons: 0b"));
			for (uint8_t i = 0; i < sizeof(ControllerState.Buttons) * 8; i++)
			{
				Serial.print((ControllerState.Buttons >> i) & 0b1);
			}
			Serial.print(F("\tJoystick: "));
			Serial.print(ControllerState.JoystickX);
			Serial.print('\t');
			Serial.print(ControllerState.JoystickY);
			Serial.println();
			Serial.print(F("\tJoystick C: "));
			Serial.print(ControllerState.JoystickCX);
			Serial.print('\t');
			Serial.print(ControllerState.JoystickCY);
			Serial.println();
			Serial.println();

			Task::delay(UpdatePeriodMicros / 1000);

			return true;
		}
		else
		{
			Task::delay(50);

			return false;
		}
	}
};

#endif

