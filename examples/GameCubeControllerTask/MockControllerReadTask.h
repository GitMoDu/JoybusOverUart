// MockControllerReadTask.h

#ifndef _MOCK_CONTROLLER_READ_TASK_h
#define _MOCK_CONTROLLER_READ_TASK_h

#define _TASK_OO_CALLBACKS
#include <TaskSchedulerDeclarations.h>

#include <GameCubeController.h>

using namespace GameCubeController;

class MockControllerReadTask : private Task
{
private:
	enum class SectionEnum : uint8_t
	{
		ABXY,
		Sliders,
		LR,
		DPad,
		StartZ,
		Disconnect,
		SectionEnumCount
	};

	static constexpr uint32_t JoyXPeriod = 2500000;
	static constexpr uint32_t JoyYPeriod = 2173333;
	static constexpr uint32_t SliderPeriod = 1776666;
	static constexpr uint32_t SectionDurationMicros = 5000000;

private:
	GameCubeController::state_data_t& ControllerState;
	uint32_t SectionStart = 0;
	SectionEnum Section = SectionEnum::ABXY;

public:
	MockControllerReadTask(Scheduler* scheduler,
		GameCubeController::state_data_t& controllerState,
		const uint32_t updatePeriodMicros = 10000)
		: Task(updatePeriodMicros / 1000, TASK_FOREVER, scheduler, false)
		, ControllerState(controllerState)
	{
	}

	void Start()
	{
		if (!Task::isEnabled())
		{
			Task::enableDelayed(0);
			ControllerState.Clear();
		}
	}

	bool Callback()
	{
		const uint32_t elapsed = micros();

		if (elapsed - SectionStart > SectionDurationMicros)
		{
			Section = (SectionEnum)((uint8_t)Section + 1);
			if ((uint8_t)Section >= (uint8_t)SectionEnum::SectionEnumCount)
			{
				Section = (SectionEnum)0;
			}
			SectionStart = elapsed;
		}

		const uint32_t abcdElapsed = (elapsed % 1000001);
		const bool d = abcdElapsed > 750000;
		const bool c = !d && abcdElapsed >= 500000;
		const bool b = !c && !d && abcdElapsed >= 250000;
		const bool a = !b && !c && !d;

		const uint16_t deltaX = ((elapsed % JoyXPeriod) * (2 * UINT8_MAX)) / (JoyXPeriod - 1);
		const uint16_t deltaY = ((elapsed % JoyYPeriod) * (2 * UINT8_MAX)) / (JoyYPeriod - 1);

		if (deltaX <= UINT8_MAX)
		{
			ControllerState.JoystickX = INT8_MIN + deltaX;
		}
		else
		{
			ControllerState.JoystickX = INT8_MIN + ((2 * UINT8_MAX) - deltaX);
		}

		if (deltaY <= UINT8_MAX)
		{
			ControllerState.JoystickY = INT8_MIN + deltaY;
		}
		else
		{
			ControllerState.JoystickY = INT8_MIN + ((2 * UINT8_MAX) - deltaY);
		}

		constexpr uint32_t offset = 3232144;
		const uint16_t deltaCX = (((elapsed + offset) % JoyXPeriod) * (2 * UINT8_MAX)) / (JoyXPeriod - 1);
		const uint16_t deltaCY = (((elapsed + offset) % JoyYPeriod) * (2 * UINT8_MAX)) / (JoyYPeriod - 1);

		if (deltaCX <= UINT8_MAX)
		{
			ControllerState.JoystickCX = INT8_MIN + deltaCX;
		}
		else
		{
			ControllerState.JoystickCX = INT8_MIN + ((2 * UINT8_MAX) - deltaCX);
		}

		if (deltaCY <= UINT8_MAX)
		{
			ControllerState.JoystickCY = INT8_MIN + deltaCY;
		}
		else
		{
			ControllerState.JoystickCY = INT8_MIN + ((2 * UINT8_MAX) - deltaCY);
		}

		const uint16_t deltaLR = ((elapsed % SliderPeriod) * (2 * UINT8_MAX)) / (SliderPeriod - 1);

		ControllerState.SliderRight = 0;
		switch (Section)
		{
		case SectionEnum::ABXY:
			ControllerState.Connected = true;
			ControllerState.Buttons = a * ControllerState.Mask<ButtonsEnum::B>();
			ControllerState.Buttons |= b * ControllerState.Mask<ButtonsEnum::A>();
			ControllerState.Buttons |= c * ControllerState.Mask<ButtonsEnum::Y>();
			ControllerState.Buttons |= d * ControllerState.Mask<ButtonsEnum::X>();
			break;
		case SectionEnum::Sliders:
			if (deltaLR <= UINT8_MAX)
			{
				ControllerState.SliderRight = deltaLR;
			}
			else
			{
				ControllerState.SliderRight = UINT8_MAX - deltaLR;
			}
			break;
		case SectionEnum::StartZ:
			ControllerState.Connected = true;
			ControllerState.Buttons = (a | c) * ControllerState.Mask<ButtonsEnum::Start>();
			ControllerState.Buttons |= (b | d) * ControllerState.Mask<ButtonsEnum::Z>();
			break;
		case SectionEnum::LR:
			ControllerState.Connected = true;
			ControllerState.Buttons = (a | c) * ControllerState.Mask<ButtonsEnum::L>();
			ControllerState.Buttons |= (b | d) * ControllerState.Mask<ButtonsEnum::R>();
			break;
		case SectionEnum::DPad:
			ControllerState.Connected = true;
			ControllerState.Buttons = a * ControllerState.Mask<ButtonsEnum::Down>();
			ControllerState.Buttons |= b * ControllerState.Mask<ButtonsEnum::Right>();
			ControllerState.Buttons |= c * ControllerState.Mask<ButtonsEnum::Up>();
			ControllerState.Buttons |= d * ControllerState.Mask<ButtonsEnum::Left>();
			break;
		case SectionEnum::Disconnect:
			ControllerState.Connected = false;
			break;
		default:
			break;
		}

		ControllerState.SliderLeft = ControllerState.SliderRight;

		return true;
	}
};
#endif