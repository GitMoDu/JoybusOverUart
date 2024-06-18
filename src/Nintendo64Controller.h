// Nintendo64Controller.h

#ifndef _NINTENDO_64_CONTROLLER_h
#define _NINTENDO_64_CONTROLLER_h

namespace Nintendo64Controller
{
	enum class ButtonsEnum : uint8_t
	{
		Right = 0,
		Left = 1,
		Down = 2,
		Up = 3,
		Start = 4,
		Z = 5,
		B = 6,
		A = 7,
		CRight = 8,
		CLeft = 9,
		CDown = 10,
		CUp = 11,
		R = 12,
		L = 13,
		ControllerReset = 15
	};

	struct data_t
	{
		uint16_t Buttons;
		int8_t JoystickX;
		int8_t JoystickY;

		void Clear()
		{
			Buttons = 0;
			JoystickX = 0;
			JoystickY = 0;
		}

		template<const ButtonsEnum button>
		constexpr uint16_t Mask()
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
			Connected = source.Connected;
			Buttons = source.Buttons;
			JoystickX = source.JoystickX;
			JoystickY = source.JoystickY;
		}

		void Clear()
		{
			Buttons = 0;
			JoystickX = 0;
			JoystickY = 0;
			Connected = false;
		}
	};

	enum class CommandCode : uint8_t
	{
		StatusCode = 0x00,
		PollCode = 0x01,
		ReadCode = 0x02,
		WriteCode = 0x03,
		ResetCode = 0xFF,
		NoCommandCode = 0xF0
	};

	enum class ResponseCode : uint8_t
	{
		ReadCode = (uint8_t)~(uint8_t)CommandCode::ReadCode,
		ResetCode = (uint8_t)~(uint8_t)CommandCode::ResetCode
	};

	enum class ResponseStatusCode : uint8_t
	{
		ErrorCRC = 0x04,
		NoPakDetected = 0x02,
		ControllerOrRumblePakDetected = 0x01,
	};

	enum class ResponseSize : uint8_t
	{
		StatusSize = 3,
		PollSize = sizeof(data_t),
		ReadSize = 32,
		WriteSize = 1,
		ResetSize = 1
	};
}
#endif