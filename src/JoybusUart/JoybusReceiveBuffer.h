// JoybusReceiveBuffer.H

#ifndef _JOYBUS_RECEIVE_BUFFER_h
#define _JOYBUS_RECEIVE_BUFFER_h

#include <stdint.h>

template<const uint8_t MaxReceiveSize>
class JoybusReceiveBuffer
{
protected:
	// The buffered response, from the converted bytes from serial.
	uint8_t ReceiveBuffer[MaxReceiveSize]{};
	uint8_t ReceiveBufferSize = 0;

protected:
	const bool IsReceiveBufferFull() {
		return ReceiveBufferSize >= MaxReceiveSize;
	}

	/// <summary>
	/// JoybusUart Implementation.
	/// </summary>
protected:
	void OnByteReceived(const uint8_t byteBuffer)
	{
		ReceiveBuffer[ReceiveBufferSize++] = byteBuffer;
	}

	const bool ResponseReady() const
	{
		return ReceiveBufferSize > 0;
	}

	void BufferDiscard()
	{
		ReceiveBufferSize = 0;
	}
};

#endif