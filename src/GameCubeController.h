// GameCubeController.h

#ifndef _GAMECUBE_CONTROLLER_h
#define _GAMECUBE_CONTROLLER_h

namespace GameCubeController
{
	enum class ButtonsEnum
	{
		A = 0,
		B = 1,
		X = 2,
		Y = 3,
		Start = 4,
		Left = 8,
		Right = 9,
		Down = 10,
		Up = 11,
		Z = 12,
		R1 = 13,
		L1 = 14
	};

	struct data_t
	{
		uint16_t Buttons;
		int8_t JoystickX;
		int8_t JoystickY;
		int8_t JoystickCX;
		int8_t JoystickCY;
		uint8_t L2;
		uint8_t R2;

		void Clear()
		{
			Buttons = 0;
			JoystickX = 0;
			JoystickY = 0;
			JoystickCX = 0;
			JoystickCY = 0;
			L2 = 0;
			R2 = 0;
		}

		template<const ButtonsEnum button>
		static constexpr uint16_t Mask()
		{
			return ((uint16_t)1) << ((uint8_t)button);
		}

		template<const ButtonsEnum button>
		const bool Button()
		{
			return Buttons & Mask<button>();
		}
	};

	struct state_data_t : public data_t
	{
		bool Connected = false;

		void CopyFrom(const state_data_t& source)
		{
			Buttons = source.Buttons;
			JoystickX = source.JoystickX;
			JoystickY = source.JoystickY;
			JoystickCX = source.JoystickCX;
			JoystickCY = source.JoystickCY;
			L2 = source.L2;
			R2 = source.R2;
			Connected = source.Connected;
		}

		void Clear()
		{
			Buttons = 0;
			JoystickX = 0;
			JoystickY = 0;
			JoystickCX = 0;
			JoystickCY = 0;
			L2 = 0;
			R2 = 0;
			Connected = false;
		}
	};

	enum class CommandCode : uint8_t
	{
		NoCommandCode = 0xFF,
		StatusCode = 0x10, //TODO:
		WakeUpCode = 0x00,
		PollCode = 0x01,
	};

	enum class ResponseSize : uint8_t
	{
		WakeUpSize = 3,	// Full transaction takes ~140 us.
		PollSize = sizeof(data_t), // Full transaction takes ~370 us.
		StatusSize = 2,	//TODO:
		ResetSize = 1
	};

	enum class PollCodeEnum : uint32_t
	{
		NoRumble = 0b000000000000001101000000,
		Rumble = 0b00000000000000110100000
	};
}

#endif