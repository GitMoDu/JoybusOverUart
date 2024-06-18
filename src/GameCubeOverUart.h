// GameCubeOverUart.H

#ifndef _GAMECUBE_OVER_UART_h
#define _GAMECUBE_OVER_UART_h

#include <GameCubeController.h>
#include "JoybusUart/JoybusReceiveBuffer.h"
#include "JoybusUart/JoybusUart.h"

using namespace GameCubeController;

class GameCubeOverUart : public JoybusUart<JoybusReceiveBuffer<(uint8_t)ResponseSize::PollSize>>
{
private:
	using BaseClass = JoybusUart<JoybusReceiveBuffer<(uint8_t)ResponseSize::PollSize>>;

private:
	CommandCode LastCommandSent = CommandCode::NoCommandCode;

public:
	GameCubeOverUart(HardwareSerial* uart)
		: BaseClass(uart)
	{}

	void WakeUpPoll()
	{
		SerialDiscard();
		BufferDiscard();

		LastCommandSent = CommandCode::WakeUpCode;
		Transmit1Byte((uint8_t)CommandCode::WakeUpCode);
	}

	void Poll()
	{
		SerialDiscard();
		BufferDiscard();

		LastCommandSent = CommandCode::PollCode;
		Transmit3Bytes((uint32_t)PollCodeEnum::NoRumble);
	}

	/// <summary>
	/// Can be called after ~1 ms of poll, if low latency is desired.
	/// </summary>
	/// <returns>True when a response was found.</returns>
	const bool ReadControllerData(data_t& controllerData, const uint8_t maxReadTries = 50)
	{
		if (GetResponse(maxReadTries))
		{
			return ProcessResponse(controllerData);
		}

		return false;
	}

private:
	const bool ProcessResponse(data_t& controllerData)
	{
		// Validate for size based on expected response.
		switch (LastCommandSent)
		{
		case CommandCode::StatusCode:
			if (ReceiveBufferSize >= (uint8_t)ResponseSize::StatusSize)
			{
				//TODO: Handle on status received.
				BufferDiscard();
				SerialDiscard();
			}
			break;
		case CommandCode::WakeUpCode:
			if (ReceiveBufferSize >= (uint8_t)ResponseSize::WakeUpSize)
			{
				BufferDiscard();
				SerialDiscard();

				return true;
			}
			break;
		case CommandCode::PollCode:
			if (ReceiveBufferSize >= (uint8_t)ResponseSize::PollSize)
			{
				//if (ResponseBuffer[1] & 0x80) // Last bit of second byte should be true.
				{
					// Update controller values.
					// 2nd bit of second byte is undefined.
					controllerData.Buttons = ReceiveBuffer[0] + ((ReceiveBuffer[1] & 0x7F) << 8);
					controllerData.JoystickX = ReceiveBuffer[2] - INT8_MAX;
					controllerData.JoystickY = ReceiveBuffer[3] - INT8_MAX;
					controllerData.JoystickCX = ReceiveBuffer[4] - INT8_MAX;
					controllerData.JoystickCY = ReceiveBuffer[5] - INT8_MAX;
					controllerData.SliderLeft = ReceiveBuffer[6];
					controllerData.SliderRight = ReceiveBuffer[7];
				}

				BufferDiscard();
				return true;
			}
			break;
		default:
			break;
		}

		return false;
	}
};

#endif