// Nintendo64OverUart.H

#ifndef _NINTENDO_64_OVER_UART_h
#define _NINTENDO_64_OVER_UART_h

#include <Nintendo64Controller.h>
#include "JoybusUart/JoybusReceiveBuffer.h"
#include "JoybusUart/JoybusUart.h"

class Nintendo64OverUart : public JoybusUart<JoybusReceiveBuffer<(uint8_t)Nintendo64Controller::ResponseSize::PollSize>>
{
private:
	using BaseClass = JoybusUart<JoybusReceiveBuffer<(uint8_t)Nintendo64Controller::ResponseSize::PollSize>>;
	using CommandCode = Nintendo64Controller::CommandCode;
	using ResponseSize = Nintendo64Controller::ResponseSize;
	using ResponseCode = Nintendo64Controller::ResponseCode;

private:
	CommandCode LastCommandSent = CommandCode::NoCommandCode;

public:
	Nintendo64OverUart(HardwareSerial* uart)
		: BaseClass(uart)
	{}

	/// <summary>
	/// To be called once per target period.
	/// </summary>
	void Poll()
	{
		LastCommandSent = CommandCode::PollCode;
		SerialDiscard();
		BufferDiscard();
		Transmit1Byte((uint8_t)CommandCode::PollCode);
	}

	/// <summary>
	/// Can be called after ~1 ms of poll, if low latency is desired.
	/// </summary>
	/// <returns>True when a response was found.</returns>
	const bool ReadControllerData(Nintendo64Controller::data_t& controllerData, const uint8_t maxReadTries = 50)
	{
		if (GetResponse(maxReadTries))
		{
			return ProcessResponse(controllerData);
		}

		return false;
	}

private:
	const bool ProcessResponse(Nintendo64Controller::data_t& controllerData)
	{
		// Validate for size based on expected response.
		switch (LastCommandSent)
		{
		case CommandCode::StatusCode:
			if (ReceiveBufferSize >= (uint8_t)ResponseSize::StatusSize)
			{
				//TODO: Handle on status received.
			}
			break;
		case CommandCode::PollCode:
			if (ReceiveBufferSize >= (uint8_t)ResponseSize::PollSize)
			{
				// Update controller values.
				// 7th bit of the second byte is undefined.
				controllerData.Buttons = ReceiveBuffer[0] + ((ReceiveBuffer[1] & 0xBF) << 8);
				controllerData.JoystickX = ReceiveBuffer[2];
				controllerData.JoystickY = ReceiveBuffer[3];

				BufferDiscard();
				return true;
			}
			break;
		case CommandCode::ReadCode:
			if (ReceiveBufferSize >= (uint8_t)ResponseSize::ReadSize)
			{
				// TODO: Handle on data read.
			}
			break;
		case CommandCode::WriteCode:
			if (ReceiveBufferSize >= (uint8_t)ResponseSize::WriteSize)
			{
				// Validate Ok response.
				if (ReceiveBuffer[0] == (uint8_t)ResponseCode::ReadCode)
				{
					//TODO: Handle on write ok.
					return true;
				}
			}
			break;
		case CommandCode::ResetCode:
			if (ReceiveBufferSize >= (uint8_t)ResponseSize::ResetSize)
			{
				// Check for Command response.
				if (ReceiveBuffer[0] == (uint8_t)ResponseCode::ResetCode)
				{
					BufferDiscard();
					return true;
				}
			}
			break;
		default:
			break;
		}

		return false;
	}
};

#endif