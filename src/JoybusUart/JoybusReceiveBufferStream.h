// JoybusReceiveBufferStream.H

#ifndef _JOYBUS_RECEIVE_BUFFER_STREAM_h
#define _JOYBUS_RECEIVE_BUFFER_STREAM_h

#include <stdint.h>

enum class JoybusReceiveStreamMode
{
	BufferedReceive,
	StreamReceive,
};

template<const uint8_t MaxResponseSize>
class JoybusReceiveBufferStream
{
protected:
	// The buffered response, from the converted bytes from serial.
	uint8_t ReceiveBuffer[MaxReceiveSize]{};
	uint8_t ReceiveBufferSize = 0;

private:
	// The stream response destination buffer, from the converted bytes from serial.
	uint8_t* StreamBuffer = nullptr;
	size_t StreamBufferSize = 0;
	size_t StreamBufferMaxSize = 0;

	JoybusReceiveStreamMode ReceiveMode = JoybusReceiveStreamMode::BufferedReceive;

protected:
	virtual void OnStreamUpdated(const size_t streamBufferSize)
	{}

	// JoybusUart Implementation.
protected:
	void OnByteReceived(const uint8_t byteBuffer)
	{
		switch (ReceiveMode)
		{
		case JoybusReceiveStreamMode::BufferedReceive:
			if (ReceiveBuffer != nullptr)
			{
				ReceiveBuffer[BufferSize++] = byteBuffer;
			}
			break;
		case JoybusReceiveStreamMode::StreamReceive:
			if (StreamBuffer != nullptr
				&& (StreamBufferSize < StreamBufferMaxSize))
			{
				StreamBuffer[StreamBufferSize++] = byteBuffer;

				this->OnStreamUpdated(StreamBufferSize);
			}
			break;
		default:
			break;
		}
	}

	void BufferDiscard()
	{
		ResponseBufferSize = 0;
	}

	// Stream Implementation.
protected:
	void SetStreamBuffer(const uint8_t* buffer, const size_t maxSize = UINT8_MAX)
	{
		StreamBuffer = buffer;
		StreamBufferMaxSize = maxSize;
	}

	void StreamBufferDiscard()
	{
		StreamBufferSize = 0;
	}

	void SetReceiveMode(const JoybusReceiveStreamMode receiveMode)
	{
		ReceiveMode = receiveMode;
	}
};

#endif