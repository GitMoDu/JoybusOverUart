/*
* Example reading Nintendo64 controller using JoybusOverUart.
*
* In order to wire this up, we need to tie the UART's Rx and Tx pins together,
* using a Schottky diode, as shown here (https://github.com/dword1511/onewire-over-uart).
* Any Arduino compatible MCU should work with this library.
* Hardware required/used is a serial port capable of 1250000 bps baud-rate.
* Interrupts aren't blocked nor used.
*
*/


#define SERIAL_BAUD_RATE 115200

#include <Nintendo64Controller.h>
#include <Nintendo64OverUart.h>

static constexpr uint32_t UpdatePeriodMillis = 100;
static constexpr HardwareSerial* JoyBusSerial = &Serial3;



Nintendo64OverUart JoyBusReader(JoyBusSerial);

Nintendo64Controller::data_t ControllerState{};
bool Connected = false;


void setup()
{
	Serial.begin(SERIAL_BAUD_RATE);

	// Serial Joy requires a start to initialize the serial hardware.
	JoyBusReader.Start();

	Serial.println(F("Nintendo 64 Controller over UART"));
}

void loop()
{
	JoyBusReader.Poll();

	delay(1);

	if (JoyBusReader.ReadControllerData(ControllerState))
	{
		if (!Connected)
		{
			Connected = true;
			Serial.println(F("Found controller!"));
		}

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
		Serial.println();

		delay(UpdatePeriodMillis - 1);
	}
	else
	{
		if (Connected)
		{
			Connected = false;
			Serial.println(F("No controller."));
		}
		delay(UpdatePeriodMillis * 4);
	}
}