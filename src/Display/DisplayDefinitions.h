// DisplayDefinitions.h
#ifndef _DISPLAY_DEFINITIONS_h
#define _DISPLAY_DEFINITIONS_h

// Pins for screen display.
#if defined(ARDUINO_ARCH_STM32F4) || defined(ARDUINO_ARCH_STM32)
#define TFT_SPI		1
#define TFT_DC		PB0
#define TFT_RST     PB1
#define TFT_CS		PA4
#define TFT_CLK		PA5
#define TFT_MOSI	PA7
#define TFT_SPI_HZ	40000000
#define TFT_I2C		0
#define TFT_SCL		PB6
#define TFT_SDA		PB7
#define TFT_I2C_HZ	1000000
#elif defined(ARDUINO_ARCH_STM32F1)
#define TFT_SPI		1
#define TFT_CS		7
#define TFT_DC		8
#define TFT_RST     9
#define TFT_CLK		UINT8_MAX
#define TFT_MOSI	UINT8_MAX
#define TFT_SPI_HZ	F_CPU/2
#define TFT_I2C		1
#define TFT_SCL		UINT8_MAX
#define TFT_SDA		UINT8_MAX
#define TFT_I2C_HZ	1000000
#elif defined(ARDUINO_ARCH_AVR)
#define TFT_CS		10
#define TFT_DC		6
#define TFT_RST		7
#define TFT_SPI		0
#define TFT_CLK		UINT8_MAX
#define TFT_MOSI	UINT8_MAX
#define TFT_SPI_HZ	0
#define TFT_I2C		2
#define TFT_SCL		UINT8_MAX
#define TFT_SDA		UINT8_MAX
#define TFT_I2C_HZ	1000000
#elif defined(ARDUINO_ARCH_ESP32)
#define TFT_CS		19
#define TFT_DC		20
#define TFT_RST		21
#define TFT_SPI		0
#define TFT_CLK		26
#define TFT_MOSI	48
#define TFT_SPI_HZ	48000000
#define TFT_I2C		1
#define TFT_SCL		18
#define TFT_SDA		17
#define TFT_I2C_HZ	1000000
#elif defined(ARDUINO_ARCH_RP2040)
#define TFT_CS		19
#define TFT_DC		20
#define TFT_RST		21
#define TFT_SPI		1
#define TFT_CLK		26
#define TFT_MOSI	27
#define TFT_SPI_HZ	48000000
#define TFT_I2C		1
#define TFT_SCL		15
#define TFT_SDA		14
#define TFT_I2C_HZ	1000000
#endif

#include <ArduinoGraphicsDrivers.h>
#include <ArduinoGraphicsCore.h>


//using ScreenDriverType = ScreenDriverSSD1306_128x64x1_I2C<TFT_SCL, TFT_SDA, TFT_RST, TFT_I2C, TFT_I2C_HZ>;
//using ScreenDriverType = ScreenDriverSSD1306_128x64x1_SPI_Dma<TFT_DC, TFT_CS, TFT_RST, TFT_CLK, TFT_MOSI, TFT_SPI, TFT_SPI_HZ>;
//using FrameBufferType = MonochromeFrameBuffer<ScreenDriverType::ScreenWidth, ScreenDriverType::ScreenHeight, MonochromeColorConverter1<5>>;

using ScreenDriverType = ScreenDriverSSD1331_96x64x8_SPI_Dma<TFT_DC, TFT_CS, TFT_RST, TFT_CLK, TFT_MOSI, TFT_SPI, TFT_SPI_HZ>;
using FrameBufferType = Color8FrameBuffer<ScreenDriverType::ScreenWidth, ScreenDriverType::ScreenHeight, ColorConverter8>;


uint8_t Buffer[FrameBufferType::BufferSize]{};
FrameBufferType FrameBuffer(Buffer);
ScreenDriverType ScreenDriver{};
#endif