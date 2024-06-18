//	JoybusUart.h
//	(Ab)uses Serial Port to emulate the OneWire-like protocol of JoyBus.
//
//	JoyBus data is LSB transmitted at a 250KHz baud rate.
//	'1' bit represented by 1uS low, 3uS high.
//	'0' bit represented by 3uS low, 1uS high.
//	Console Stop bit as 1uS low, 2uS high.
//
//	In order to wire this up, we need to tie the UART's Rx and Tx pins together
//		using a Schottky diode, as shown here (https://github.com/dword1511/onewire-over-uart).
//
//	Hardware baudrate is set for a factor of the JoyBus baudrate.
//	The factor is the number of serial bytes required for a full byte + 1 for stop bit.
//
//	"This results in a timing instead of 1uS and 3uS, we get 0.8uS and 3.2uS.
//	However, this seems to still work just fine."
//
//	The controller expects a stop bit as 1uS low, 2uS high,
//	so we send a purposefully long low, to delay the response until the end of our stop code.
//	This way we don't lose the first 2 bits of the response and just eat the stop code as another echo.
//	
//	Echo bytes are the transmitted bit codes and are discarded based on the transmit size.
//
//	Any Arduino compatible MCU should work with this library, 
//	Hardware required/used is a serial port capable of 1250000 bps baud-rate.
//	Interrupts aren't blocked nor used.


#ifndef _JOYBUS_UART_h
#define _JOYBUS_UART_h

#include <HardwareSerial.h>
#include <stdint.h>

/// <summary>
/// 
/// </summary>
/// <typeparam name="ReceiverType"></typeparam>
template<typename ReceiverType>
class JoybusUart : public ReceiverType
{
private:
	//	JoyBus protocol baud-rate.
	static constexpr uint32_t RealBaudrate = 250000;

	// Each converted byte gives 2 bits.
	static constexpr uint8_t ByteBits = 2;

	// We need 4 bytes of codes to fill a byte.
	static constexpr uint8_t BytesPerByte = 8 / ByteBits;

	// The real hardware baud-rate of 1250000 bps.
	static constexpr uint32_t ConverterBaudrate = RealBaudrate * (BytesPerByte + 1);

	// Data codes converted to serial values.
	enum class BitPair : uint8_t
	{
		Code00 = 0x08,
		Code01 = 0xE8,
		Code10 = 0x0F,
		Code11 = 0xEF
	};

	// Stop bit codes converted to serial values.
	enum class BitCode : uint8_t
	{
		CodeMasterStop = 0x00,
		CodeSlaveStop = 0xFE,
		// Can happen in slight serial mis-timing. 
		CodeSlaveStopAlternate = 0xFC
	};

	// The incoming byte buffer.
	uint8_t ByteBuffer = 0;
	uint8_t ByteIndex = 0;

	// Transmited bytes expected to discard.
	uint8_t EchoBytes = 0;

	// The serial port used.
	//	In order to wire this up, we need to tie the UART's Rx and Tx pins together
	//	using a Schottky diode, as shown here (https://github.com/dword1511/onewire-over-uart).
	HardwareSerial* SerialInstance;

protected:
	//// The buffered response, from the converted bytes from serial.
	//uint8_t ResponseBuffer[MaxResponseSize]{};
	//uint8_t ResponseBufferSize = 0;

public:
	JoybusUart(HardwareSerial* serial)
		: ReceiverType()
		, SerialInstance(serial)
	{}

	void Start()
	{
		SerialInstance->begin(ConverterBaudrate);
		SerialInstance->flush();
		SerialDiscard();
		ReceiverType::BufferDiscard();
	}

	void Stop()
	{
		ReceiverType::BufferDiscard();
		SerialDiscard();
		SerialInstance->clearWriteError();
		SerialInstance->end();
	}

	/// <summary>
	/// Inline test of Uart echo.
	/// Checks if the Tx/Rx line are wired up correctly.
	/// </summary>
	/// <returns>True if Uart echo is as expected.</returns>
	const bool TestEcho()
	{
		constexpr uint8_t echoSize = 5;

		SerialDiscard();
		for (uint8_t i = 0; i < echoSize; i++)
		{
			SerialInstance->write(i);
		}

		delay(1);

		for (uint8_t i = 0; i < echoSize; i++)
		{
			if (!SerialInstance->available()
				|| SerialInstance->read() != i)
			{
				return false;
			}
		}

		return true;
	}

private:
	// Returns true on stop bit code detected.
	const bool ReadByte()
	{
		const uint8_t bitPairCode = SerialInstance->read();

		// LSB reception.
		// Bits are inverted in order, 
		// as we build up a whole byte, from the top.
		switch (bitPairCode)
		{
		case (uint8_t)BitPair::Code00:
			// ByteBuffer += 0b00 << ((BytesPerByte - ByteIndex) * ByteBits);
			ByteIndex++;
			break;
		case (uint8_t)BitPair::Code01:
			ByteBuffer += 0b01 << ((BytesPerByte - ByteIndex - 1) * ByteBits);
			ByteIndex++;
			break;
		case (uint8_t)BitPair::Code10:
			ByteBuffer += 0b10 << ((BytesPerByte - ByteIndex - 1) * ByteBits);
			ByteIndex++;
			break;
		case (uint8_t)BitPair::Code11:
			ByteBuffer += 0b11 << ((BytesPerByte - ByteIndex - 1) * ByteBits);
			ByteIndex++;
			break;
		case (uint8_t)BitCode::CodeSlaveStop:
		case (uint8_t)BitCode::CodeSlaveStopAlternate:
			SerialDiscard();
			return true;
		default:// Invalid code received, message is invalidated.
			ReceiverType::BufferDiscard();
			SerialDiscard();
			break;
		}

		if (ByteIndex >= BytesPerByte)
		{	// Message byte end.
			ReceiverType::OnByteReceived(ByteBuffer);
			ByteBuffer = 0;
			ByteIndex = 0;
		}

		return false;
	}

protected:
	/// <summary>
	/// Tries to fill the receive buffer until serial input is clear or the receive buffer is full.
	/// </summary>
	/// <param name="maxReadTries">Limit how many serial characters are read for each call.</param>
	/// <returns>True when a message is available.</returns>
	const bool GetResponse(const uint8_t maxReadTries = 50)
	{
		uint8_t tries = 0;
		while (tries < maxReadTries
			&& SerialInstance->available())
		{
			// Discard echo bytes.
			if (EchoBytes > 0)
			{
				SerialInstance->read();
				EchoBytes--;
			}
			else if (ReadByte())
			{
				// Stop bit detected, message received.
				return ReceiverType::ResponseReady();
			}

			tries++;
		}

		return false;
	}

	// Pushes 3 bytes, 2 bits at a time to the serial buffer.
	void Transmit3Bytes(const uint32_t lower3bytes)
	{
		// Send 24 bits, 2 bits at a time.
		for (uint8_t i = 0; i < 3; i++)
		{
			uint8_t byteValue = (lower3bytes >> (i * 8)) & 0xFF;
			WriteByte(byteValue);
		}

		SerialInstance->write((uint8_t)BitCode::CodeMasterStop);

		// Expected echo bytes: 4 bit pairs and 1 stop code.
		EchoBytes = (BytesPerByte * 3) + 1;
	}

	// Pushes 1 byte, 2 bits at a time to the serial buffer.
	void Transmit1Byte(const uint8_t value)
	{
		WriteByte(value);

		SerialInstance->write((uint8_t)BitCode::CodeMasterStop);

		// Expected echo bytes: 4 bit pairs and 1 stop code.
		EchoBytes = BytesPerByte + 1;
	}

	void SerialDiscard()
	{
		while (SerialInstance->available())
		{
			SerialInstance->read();
		}

		EchoBytes = 0;

		// Reset byte buffer.
		ByteBuffer = 0;
		ByteIndex = 0;
	}

private:
	void WriteByte(const uint8_t value)
	{
		// Send 8 bits, in 4 x 2 bits at a time.
		// Initiate write command by bringing the line down with the first bit pair.
		for (uint8_t i = 0; i < (BytesPerByte * ByteBits); i += ByteBits)
		{
			// LSB transmission.
			uint8_t bitPair;
			bitPair = ((value >> (6 - i)) & 0b1) + (((value >> (7 - i)) & 0b1) << 1);

			switch (bitPair)
			{
			case 0b00:
				SerialInstance->write((uint8_t)BitPair::Code00);
				break;
			case 0b01:
				SerialInstance->write((uint8_t)BitPair::Code01);
				break;
			case 0b10:
				SerialInstance->write((uint8_t)BitPair::Code10);
				break;
			case 0b11:
				SerialInstance->write((uint8_t)BitPair::Code11);
				break;
			default:
				return;
			}
		}
	}
};
#endif