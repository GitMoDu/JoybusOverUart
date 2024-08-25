// MockControllerReadTask.h

#ifndef _MOCK_CONTROLLER_READ_TASK_h
#define _MOCK_CONTROLLER_READ_TASK_h

#define _TASK_OO_CALLBACKS
#include <TaskSchedulerDeclarations.h>

#include <Nintendo64Controller.h>

using namespace Nintendo64Controller;

class MockControllerReadTask : private Task
{
private:
	enum class SectionEnum : uint8_t
	{
		AB,
		C,
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
	Nintendo64Controller::state_data_t& ControllerState;
	uint32_t SectionStart = 0;
	SectionEnum Section = SectionEnum::AB;

public:
	MockControllerReadTask(Scheduler* scheduler,
		Nintendo64Controller::state_data_t& controllerState,
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

		const uint8_t deltaX = ((elapsed % JoyXPeriod) * UINT8_MAX) / (JoyXPeriod - 1);
		const uint8_t deltaY = ((elapsed % JoyYPeriod) * UINT8_MAX) / (JoyYPeriod - 1);

		if (deltaX <= INT8_MAX)
		{
			ControllerState.JoystickX = (INT8_MIN / 2) + deltaX;
		}
		else
		{
			ControllerState.JoystickX = (INT8_MIN / 2) + (UINT8_MAX - deltaX);
		}

		if (deltaY <= INT8_MAX)
		{
			ControllerState.JoystickY = (INT8_MIN / 2) + deltaY;
		}
		else
		{
			ControllerState.JoystickY = (INT8_MIN / 2) + (UINT8_MAX - deltaY);
		}

		switch (Section)
		{
		case SectionEnum::AB:
			ControllerState.Connected = true;
			ControllerState.Buttons = (a | c) * ControllerState.Mask<ButtonsEnum::A>();
			ControllerState.Buttons |= (b | d) * ControllerState.Mask<ButtonsEnum::B>();
			break;
		case SectionEnum::C:
			ControllerState.Connected = true;
			ControllerState.Buttons = a * ControllerState.Mask<ButtonsEnum::CDown>();
			ControllerState.Buttons |= b * ControllerState.Mask<ButtonsEnum::CRight>();
			ControllerState.Buttons |= c * ControllerState.Mask<ButtonsEnum::CUp>();
			ControllerState.Buttons |= d * ControllerState.Mask<ButtonsEnum::CLeft>();
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

		return true;
	}
};
#endif