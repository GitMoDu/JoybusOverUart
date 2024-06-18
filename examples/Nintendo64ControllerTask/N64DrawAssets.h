// N64DrawAssets.h

#ifndef _N64_DRAW_ASSETS_h
#define _N64_DRAW_ASSETS_h

#include <stdint.h>

namespace N64DrawAssets
{
	namespace Pallete
	{
		static constexpr uint8_t Black = 0;

		static constexpr uint32_t WhitePadRGB = 0xB5AAB1;
		static constexpr uint32_t WhiteDeepRGB = 0x726B70;
		static constexpr uint32_t GrayPadRGB = 0x726B6F;

		static constexpr uint16_t WhitePad = 0xb556;
		static constexpr uint16_t WhiteDeep = 0x9c72;
		static constexpr uint16_t GrayPad = 0x734d;
		static constexpr uint16_t GrayDeepPad = 0x41e8;
		static constexpr uint16_t GrayShallowPad = 0x736e;


		static constexpr int8_t HighlightTint = 100;
		static constexpr int8_t HighlightTintSoft = 70;
		static constexpr int8_t HighlightTintStrong = 110;
		static constexpr int8_t DisconnectTint = -90;
		static constexpr int8_t DisconnectTintSoft = -60;
	}

	namespace JoyLimits
	{
		static constexpr uint8_t Diameter = 25;
		static constexpr int8_t Octshift = 3;
	}

	namespace ShoulderL
	{
		static constexpr uint8_t Width = 24;
		static constexpr uint8_t Height = 7;

		static constexpr uint8_t Bitmask[] PROGMEM{
			0b00000111, 0b11111111, 0b11111111,
			0b00011111, 0b11111111, 0b11111111,
			0b01111111, 0b11111111, 0b11111111,
			0b11111111, 0b11111111, 0b11111111,
			0b11111100, 0b00000000, 0b00000000,
			0b11110000, 0b00000000, 0b00000000,
			0b11000000, 0b00000000, 0b00000000
		};
	}

	namespace Joystick
	{
		static constexpr uint8_t Width = 15;
		static constexpr uint8_t Height = 15;

		static constexpr uint16_t Bitmap[] PROGMEM{
			Pallete::Black, Pallete::Black, Pallete::Black, Pallete::Black, 0x41e7, 0x83cf, 0xa4f4, Pallete::WhitePad, 0xa4f4, 0x83cf, 0x41e7, Pallete::Black, Pallete::Black, Pallete::Black, Pallete::Black,
			Pallete::Black, Pallete::Black, 0x18c3, 0x9452, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhitePad, 0x9452, 0x18c3, Pallete::Black, Pallete::Black,
			Pallete::Black, 0x18c3, 0xa4f4, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhiteDeep, Pallete::WhiteDeep, Pallete::WhiteDeep, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, 0xa4f4, 0x18c3, Pallete::Black,
			Pallete::Black, 0x9452, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, 0x9452, Pallete::Black,
			0x41e7, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhiteDeep, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, 0x41e8,
			0x83cf, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, 0x83d0,
			0xa4f4, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, 0xacf4,
			Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhiteDeep, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad,
			0xa4f4, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, 0xacf4,
			0x83cf, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, 0x83f0,
			0x41e8, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhiteDeep, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, 0x4208,
			Pallete::Black, 0x9452, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, 0x9472, Pallete::Black,
			Pallete::Black, 0x18c3, 0xa4f4, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhiteDeep, Pallete::WhiteDeep, Pallete::WhiteDeep, Pallete::WhiteDeep, Pallete::WhiteDeep, Pallete::WhitePad, Pallete::WhitePad, 0xa4f4, 0x18e3, Pallete::Black,
			Pallete::Black, Pallete::Black, 0x18c3, 0x9472, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhitePad, Pallete::WhitePad, 0x9472, 0x18e3, Pallete::Black, Pallete::Black,
			Pallete::Black, Pallete::Black, Pallete::Black, Pallete::Black, 0x4208, 0x83f0, 0xacf4, Pallete::WhitePad, 0xacf4, 0x83f0, 0x4208, Pallete::Black, Pallete::Black, Pallete::Black, Pallete::Black
		};
	}

	namespace DPadUp
	{
		static constexpr uint8_t Width = 5;
		static constexpr uint8_t Height = 5;

		static constexpr uint16_t Bitmap[] PROGMEM{
			0x736e, 0x736e, 0x736e, 0x736e, 0x736e,
			0x736e, Pallete::GrayPad, 0x5acb, Pallete::GrayPad, 0x736e,
			0x736e, 0x6b0c, Pallete::GrayDeepPad, 0x6b0c, 0x736e,
			0x736e, 0x5249, Pallete::GrayDeepPad, 0x5249, 0x736e,
			0x736e, 0x736e, 0x736e, 0x736e, 0x736e
		};
	}

	namespace DPadLeft
	{
		static constexpr uint8_t Width = 5;
		static constexpr uint8_t Height = 5;

		static constexpr uint16_t Bitmap[] PROGMEM{
			0x736e, 0x736e, 0x736e, 0x736e, 0x736e,
			0x736e, Pallete::GrayPad, 0x6b0c, 0x5249, 0x736e,
			0x736e, 0x5acb, Pallete::GrayDeepPad, Pallete::GrayDeepPad, 0x736e,
			0x736e, Pallete::GrayPad, 0x6b0c, 0x5249, 0x736e,
			0x736e, 0x736e, 0x736e, 0x736e, 0x736e
		};
	}

	namespace DPadCenter
	{
		static constexpr uint8_t Width = 5;
		static constexpr uint8_t Height = 5;

		static constexpr uint16_t Bitmap[] PROGMEM{
			0x736e, 0x736e, Pallete::GrayPad, 0x736e, 0x736e,
			0x736e, 0x528a, Pallete::GrayDeepPad, 0x526a, 0x736e,
			Pallete::GrayPad, Pallete::GrayDeepPad, Pallete::GrayDeepPad, Pallete::GrayDeepPad, Pallete::GrayPad,
			0x736e, 0x526a, Pallete::GrayDeepPad, 0x526a, 0x736e,
			0x736e, 0x736e, Pallete::GrayPad, 0x736e, 0x736e
		};
	}

	namespace ButtonZ
	{
		static constexpr uint8_t Width = 8;
		static constexpr uint8_t Height = 13;

		static constexpr uint16_t Bitmap[] PROGMEM{
			Pallete::GrayShallowPad, Pallete::GrayShallowPad, Pallete::GrayShallowPad, Pallete::GrayShallowPad, Pallete::GrayShallowPad, Pallete::GrayShallowPad, Pallete::GrayShallowPad, Pallete::GrayShallowPad,
			Pallete::GrayShallowPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayShallowPad,
			Pallete::GrayShallowPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayShallowPad,
			Pallete::GrayShallowPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayShallowPad,
			Pallete::GrayShallowPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayShallowPad,
			Pallete::GrayShallowPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayShallowPad,
			Pallete::GrayShallowPad, Pallete::GrayPad, Pallete::GrayDeepPad, Pallete::GrayDeepPad, Pallete::GrayDeepPad, Pallete::GrayDeepPad, Pallete::GrayPad, Pallete::GrayShallowPad,
			Pallete::GrayShallowPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayDeepPad, Pallete::GrayPad, Pallete::GrayShallowPad,
			Pallete::GrayShallowPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayDeepPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayShallowPad,
			Pallete::GrayShallowPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayDeepPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayShallowPad,
			Pallete::GrayShallowPad, Pallete::GrayPad, Pallete::GrayDeepPad, Pallete::GrayDeepPad, Pallete::GrayDeepPad, Pallete::GrayDeepPad, Pallete::GrayPad, Pallete::GrayShallowPad,
			Pallete::GrayShallowPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayPad, Pallete::GrayShallowPad,
			Pallete::GrayDeepPad, Pallete::GrayDeepPad, Pallete::GrayDeepPad, Pallete::GrayDeepPad, Pallete::GrayDeepPad, Pallete::GrayDeepPad, Pallete::GrayDeepPad, Pallete::GrayDeepPad
		};
	}

	namespace ButtonA
	{
		static constexpr uint8_t Width = 10;
		static constexpr uint8_t Height = 10;

		static constexpr uint16_t Bitmap[] PROGMEM{
			Pallete::Black, Pallete::Black, Pallete::Black, 0x0217, 0x09b5, 0x09b5, 0x09b5, Pallete::Black, Pallete::Black, Pallete::Black,
			Pallete::Black, 0x0217, 0x09b5, 0x09b5, 0x09b5, 0x09b5, 0x09b5, 0x09b5, 0x09b5, Pallete::Black,
			Pallete::Black, 0x0217, 0x09b5, 0x00c9, 0x00c9, 0x09b5, 0x09b5, 0x09b5, 0x09b5, Pallete::Black,
			0x0217, 0x09b5, 0x00c9, 0x09b5, 0x09b5, 0x00c9, 0x09b5, 0x09b5, 0x09b5, 0x014f,
			0x0217, 0x09b5, 0x00c9, 0x09b5, 0x09b5, 0x00c9, 0x09b5, 0x09b5, 0x09b5, 0x014f,
			0x0217, 0x09b5, 0x00c9, 0x00c9, 0x00c9, 0x00c9, 0x09b5, 0x09b5, 0x09b5, 0x014f,
			0x0217, 0x09b5, 0x00c9, 0x09b5, 0x09b5, 0x00c9, 0x09b5, 0x09b5, 0x09b5, 0x014f,
			Pallete::Black, 0x09b5, 0x00c9, 0x09b5, 0x09b5, 0x00c9, 0x09b5, 0x09b5, 0x014f, Pallete::Black,
			Pallete::Black, 0x09b5, 0x09b5, 0x09b5, 0x09b5, 0x09b5, 0x09b5, 0x014f, 0x014f, Pallete::Black,
			Pallete::Black, Pallete::Black, Pallete::Black, 0x014f, 0x014f, 0x014f, 0x014f, Pallete::Black, Pallete::Black, Pallete::Black
		};
	}

	namespace ButtonB
	{
		static constexpr uint8_t Width = 10;
		static constexpr uint8_t Height = 10;

		static constexpr uint16_t Bitmap[] PROGMEM{
			Pallete::Black, Pallete::Black, Pallete::Black, 0x04f1, 0x04f1, 0x04f1, 0x040e, Pallete::Black, Pallete::Black, Pallete::Black,
			Pallete::Black, 0x04f1, 0x04f1, 0x040e, 0x040e, 0x040e, 0x040e, 0x040e, 0x040e, Pallete::Black,
			Pallete::Black, 0x04f1, 0x0268, 0x0268, 0x0268, 0x040e, 0x040e, 0x040e, 0x040e, Pallete::Black,
			0x04f1, 0x040e, 0x0268, 0x040e, 0x040e, 0x0268, 0x040e, 0x040e, 0x040e, 0x034b,
			0x04f1, 0x040e, 0x0268, 0x040e, 0x040e, 0x0268, 0x040e, 0x040e, 0x040e, 0x034b,
			0x04f1, 0x040e, 0x0268, 0x0268, 0x0268, 0x040e, 0x040e, 0x040e, 0x040e, 0x034b,
			0x04f1, 0x040e, 0x0268, 0x040e, 0x040e, 0x0268, 0x040e, 0x040e, 0x040e, 0x034b,
			Pallete::Black, 0x040e, 0x0268, 0x0268, 0x0268, 0x040e, 0x040e, 0x040e, 0x034b, Pallete::Black,
			Pallete::Black, 0x040e, 0x040e, 0x040e, 0x040e, 0x040e, 0x040e, 0x034b, 0x034b, Pallete::Black,
			Pallete::Black, Pallete::Black, Pallete::Black, 0x034b, 0x034b, 0x034b, 0x034b, Pallete::Black, Pallete::Black, Pallete::Black
		};
	}

	namespace ButtonStart
	{
		static constexpr uint8_t Width = 9;
		static constexpr uint8_t Height = 9;

		static constexpr uint16_t Bitmap[] PROGMEM{
			Pallete::Black, Pallete::Black, 0xfae9, 0xfae9, 0xfae9, 0xfae9, 0xfae9, Pallete::Black, Pallete::Black,
			Pallete::Black, 0xfae9, 0xfa46, 0xfa46, 0xfa46, 0xfa46, 0xfa46, 0xfa46, Pallete::Black,
			0xfae9, 0xfa46, 0xfa46, 0x8943, 0x8943, 0x8943, 0xfa46, 0xfa46, 0xb1a4,
			0xfae9, 0xfa46, 0xfa46, 0x8943, 0xfa46, 0xfa46, 0xfa46, 0xfa46, 0xb1a4,
			0xfae9, 0xfa46, 0xfa46, 0x8943, 0x8943, 0x8943, 0xfa46, 0xfa46, 0xb1a4,
			0xfae9, 0xfa46, 0xfa46, 0xfa46, 0xfa46, 0x8943, 0xfa46, 0xfa46, 0xb1a4,
			0xfae9, 0xfa46, 0xfa46, 0x8943, 0x8943, 0x8943, 0xfa46, 0xfa46, 0xb1a4,
			Pallete::Black, 0xfa46, 0xfa46, 0xfa46, 0xfa46, 0xfa46, 0xfa46, 0xb1a4, Pallete::Black,
			Pallete::Black, Pallete::Black, 0xb1a4, 0xb1a4, 0xb1a4, 0xb1a4, 0xb1a4, Pallete::Black, Pallete::Black
		};
	}

	namespace ButtonC
	{
		static constexpr uint8_t Width = 7;
		static constexpr uint8_t Height = 7;

		static constexpr uint16_t BitmapUp[] PROGMEM{
			Pallete::Black, Pallete::Black, 0xff03, 0xff03, 0xff03, Pallete::Black, Pallete::Black,
			Pallete::Black, 0xff03, 0xff03, 0xaca2, 0xff03, 0xff03, Pallete::Black,
			0xff03, 0xff03, 0xaca2, 0xaca2, 0xaca2, 0xff03, 0xff03,
			0xff03, 0xaca2, 0xaca2, 0xaca2, 0xaca2, 0xaca2, 0xff03,
			0xe643, 0xff03, 0xff03, 0xff03, 0xff03, 0xff03, 0xe643,
			Pallete::Black, 0xe643, 0xff03, 0xff03, 0xff03, 0xe643, Pallete::Black,
			Pallete::Black, Pallete::Black, 0xe643, 0xe643, 0xe643, Pallete::Black, Pallete::Black
		};

		static constexpr uint16_t BitmapDown[] PROGMEM{
			Pallete::Black, Pallete::Black, 0xff4c, 0xff4c, 0xff4c, Pallete::Black, Pallete::Black,
			Pallete::Black, 0xff4c, 0xff03, 0xff03, 0xff03, 0xff03, Pallete::Black,
			0xff4c, 0xff03, 0xff03, 0xff03, 0xff03, 0xff03, 0xe643,
			0xff4c, 0xaca2, 0xaca2, 0xaca2, 0xaca2, 0xaca2, 0xe643,
			0xff4c, 0xff03, 0xaca2, 0xaca2, 0xaca2, 0xff03, 0xe643,
			Pallete::Black, 0xff03, 0xff03, 0xaca2, 0xff03, 0xe643, Pallete::Black,
			Pallete::Black, Pallete::Black, 0xe643, 0xe643, 0xe643, Pallete::Black, Pallete::Black
		};

		static constexpr uint16_t BitmapLeft[] PROGMEM{
			Pallete::Black, Pallete::Black, 0xff4c, 0xff4c, 0xff4c, Pallete::Black, Pallete::Black,
			Pallete::Black, 0xff4c, 0xff03, 0xaca2, 0xff03, 0xff03, Pallete::Black,
			0xff4c, 0xff03, 0xaca2, 0xaca2, 0xff03, 0xff03, 0xe643,
			0xff4c, 0xaca2, 0xaca2, 0xaca2, 0xff03, 0xff03, 0xe643,
			0xff4c, 0xff03, 0xaca2, 0xaca2, 0xff03, 0xff03, 0xe643,
			Pallete::Black, 0xff03, 0xff03, 0xaca2, 0xff03, 0xe643, Pallete::Black,
			Pallete::Black, Pallete::Black, 0xe643, 0xe643, 0xe643, Pallete::Black, Pallete::Black
		};

		static constexpr uint16_t BitmapRight[] PROGMEM{
			Pallete::Black, Pallete::Black, 0xff4c, 0xff4c, 0xff4c, Pallete::Black, Pallete::Black,
			Pallete::Black, 0xff4c, 0xff03, 0xaca2, 0xff03, 0xff03, Pallete::Black,
			0xff4c, 0xff03, 0xff03, 0xaca2, 0xaca2, 0xff03, 0xe643,
			0xff4c, 0xff03, 0xff03, 0xaca2, 0xaca2, 0xaca2, 0xe643,
			0xff4c, 0xff03, 0xff03, 0xaca2, 0xaca2, 0xff03, 0xe643,
			Pallete::Black, 0xff03, 0xff03, 0xaca2, 0xff03, 0xe643, Pallete::Black,
			Pallete::Black, Pallete::Black, 0xe643, 0xe643, 0xe643, Pallete::Black, Pallete::Black
		};
	}

	namespace Icon
	{
		static constexpr uint8_t Width = 13;
		static constexpr uint8_t Height = 13;

		static constexpr uint16_t Bitmap[] PROGMEM{
			0x0000, 0x0000, 0x0000, 0x1082, 0x7bd0, 0xa515, 0xad55, 0x94d4, 0x6b6e, 0x0841, 0x0000, 0x0000, 0x0000,
			0x0000, 0x528a, 0x94b3, 0xbdd7, 0xbe19, 0xad97, 0xad76, 0xa556, 0x9d15, 0x8c72, 0x8432, 0x3a09, 0x0000,
			0x4208, 0xce7a, 0xc639, 0xce5a, 0xbdf8, 0xb597, 0xad96, 0xa556, 0xa515, 0x9d36, 0xbd94, 0xad13, 0x2967,
			0x94b3, 0xad97, 0x7c11, 0xbdd8, 0xbe19, 0xb5b7, 0xad97, 0xad76, 0x9d36, 0xb574, 0xcd4f, 0xc52e, 0x736d,
			0xa535, 0x9cf4, 0x632e, 0xa555, 0xbe39, 0xb597, 0xc38f, 0xb576, 0x7d33, 0x5c0f, 0xbd31, 0xb4ef, 0x73d0,
			0xc639, 0xce5a, 0xb5b7, 0xc639, 0xbdf8, 0xb5b7, 0xacf4, 0xad77, 0xa555, 0x5bd5, 0x6bb4, 0x9cf4, 0x8452,
			0xdedb, 0xc639, 0xad56, 0x8c72, 0xbdf8, 0xad76, 0x7411, 0x7c11, 0xa535, 0x73b0, 0x8c93, 0xa535, 0x94b4,
			0xce59, 0xb5d8, 0x3a08, 0x0000, 0x5acb, 0xad76, 0xad77, 0x5b0d, 0x4a49, 0x0000, 0x630c, 0xb5b7, 0x8c72,
			0xb596, 0xb5d8, 0x1904, 0x0000, 0x2945, 0xad97, 0x7c11, 0x8c72, 0x2125, 0x0000, 0x3186, 0xb5d8, 0x7bf0,
			0x7bcf, 0xad76, 0x0000, 0x0000, 0x1082, 0xad97, 0xb5b7, 0xa535, 0x0862, 0x0000, 0x0020, 0xad76, 0x5acc,
			0x0841, 0x10a3, 0x0000, 0x0000, 0x0000, 0x94b3, 0xb5b7, 0x8c72, 0x0000, 0x0000, 0x0000, 0x18c3, 0x0841,
			0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x6b6e, 0xb5d7, 0x630c, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2945, 0xad56, 0x2104, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
		};
	}

	struct IconBitmapSprite : public FlashBitmapRgb565Sprite<Icon::Width, Icon::Height>
	{
		IconBitmapSprite() : FlashBitmapRgb565Sprite<Icon::Width, Icon::Height>(Icon::Bitmap)
		{}
	};

	struct ButtonABitmapSprite : public FlashBitmapRgb565Sprite<ButtonA::Width, ButtonA::Height>
	{
		ButtonABitmapSprite() : FlashBitmapRgb565Sprite<ButtonA::Width, ButtonA::Height>(ButtonA::Bitmap)
		{}
	};
	struct ButtonBBitmapSprite : public FlashBitmapRgb565Sprite<ButtonB::Width, ButtonB::Height>
	{
		ButtonBBitmapSprite() : FlashBitmapRgb565Sprite<ButtonB::Width, ButtonB::Height>(ButtonB::Bitmap)
		{}
	};

	struct ButtonStartBitmapSprite : public FlashBitmapRgb565Sprite<ButtonStart::Width, ButtonStart::Height>
	{
		ButtonStartBitmapSprite() : FlashBitmapRgb565Sprite<ButtonStart::Width, ButtonStart::Height>(ButtonStart::Bitmap)
		{}
	};

	struct ShoulderLBitmaskSprite : public FlashBitMaskSprite<ShoulderL::Width, ShoulderL::Height>
	{
		ShoulderLBitmaskSprite() : FlashBitMaskSprite<ShoulderL::Width, ShoulderL::Height>(ShoulderL::Bitmask)
		{}
	};

	struct DPadUpBitmapSprite : public FlashBitmapRgb565Sprite<DPadUp::Width, DPadUp::Height>
	{
		DPadUpBitmapSprite() : FlashBitmapRgb565Sprite<DPadUp::Width, DPadUp::Height>(DPadUp::Bitmap)
		{}
	};

	struct DPadLeftBitmapSprite : public FlashBitmapRgb565Sprite<DPadLeft::Width, DPadLeft::Height>
	{
		DPadLeftBitmapSprite() : FlashBitmapRgb565Sprite<DPadLeft::Width, DPadLeft::Height>(DPadLeft::Bitmap)
		{}
	};

	struct DPadCenterBitmapSprite : public FlashBitmapRgb565Sprite<DPadCenter::Width, DPadCenter::Height>
	{
		DPadCenterBitmapSprite() : FlashBitmapRgb565Sprite<DPadCenter::Width, DPadCenter::Height>(DPadCenter::Bitmap)
		{}
	};

	struct JoystickBitmapSprite : public FlashBitmapRgb565Sprite<Joystick::Width, Joystick::Height>
	{
		JoystickBitmapSprite() : FlashBitmapRgb565Sprite<Joystick::Width, Joystick::Height>(Joystick::Bitmap)
		{}
	};

	struct ButtonZBitmapSprite : public FlashBitmapRgb565Sprite<ButtonZ::Width, ButtonZ::Height>
	{
		ButtonZBitmapSprite() : FlashBitmapRgb565Sprite<ButtonZ::Width, ButtonZ::Height>(ButtonZ::Bitmap)
		{}
	};

	struct ButtonCBitmapSprite : public FlashBitmapRgb565Sprite<ButtonC::Width, ButtonC::Height>
	{
		ButtonCBitmapSprite() : FlashBitmapRgb565Sprite<ButtonC::Width, ButtonC::Height>(ButtonC::BitmapUp)
		{}

		void SetUp()
		{
			SetBitmap(ButtonC::BitmapUp);
		}

		void SetRight()
		{
			SetBitmap(ButtonC::BitmapRight);
		}

		void SetLeft()
		{
			SetBitmap(ButtonC::BitmapLeft);
		}

		void SetDown()
		{
			SetBitmap(ButtonC::BitmapDown);
		}
	};

	template<const uint8_t OffsetX,
		const uint8_t OffsetY,
		const uint8_t Width,
		const uint8_t Height>
	struct N64ControllerLayout
	{
		static constexpr uint8_t GetJoystickScale()
		{
			return (JoyLimits::Diameter - ((uint16_t)Joystick::Width / 8)) / 2;
		}

		static constexpr uint8_t GetButtonsAvailableWidth()
		{
			return (Width / 2) - (ButtonStart::Width / 2);
		}

		static constexpr uint8_t GetButtonsWidth()
		{
			return (1 * ButtonA::Width) + (ButtonA::Width / 3) + (2 * ButtonC::Width) - 1;
		}

		static constexpr uint8_t GetDPadDiameter()
		{
			return (2 * DPadUp::Height) + DPadCenter::Height;
		}

		static constexpr uint8_t GetLX()
		{
			return OffsetX;
		}

		static constexpr uint8_t GetRX()
		{
			return OffsetX + Width - 1 - ShoulderL::Width;
		}

		static constexpr uint8_t GetLRY()
		{
			return OffsetY;
		}

		static constexpr uint8_t GetZX()
		{
			return GetDPadX() + (GetDPadDiameter() / 4) + 1;
		}

		static constexpr uint8_t GetZY()
		{
			return GetJoyLimitsY() + (((Height / 2) - ButtonZ::Height) / 2);
		}

		static constexpr uint8_t GetDPadX()
		{
			return OffsetX + ((GetButtonsAvailableWidth() - GetButtonsWidth()) / 2) - 2;
		}

		static constexpr uint8_t GetDPadY()
		{
			return GetButtonCUpY() + 2;
		}

		static constexpr uint8_t GetButtonsStartX()
		{
			return OffsetX + (Width / 2) + (GetButtonsAvailableWidth() - GetButtonsWidth()) / 2;
		}

		static constexpr uint8_t GetJoyLimitsX()
		{
			return (((uint16_t)GetDPadX() + GetDPadDiameter() + GetButtonStartX()) / 2) - (Joystick::Width / 3);
		}

		static constexpr uint8_t GetJoyLimitsY()
		{
			return GetButtonsCenterY() + (ButtonStart::Height / 2) + 1;
		}

		static constexpr uint8_t GetJoyHeadX()
		{
			return GetJoyLimitsX() + ((JoyLimits::Diameter - Joystick::Width) / 2);
		}

		static constexpr uint8_t GetJoyHeadY()
		{
			return GetJoyLimitsY() + ((JoyLimits::Diameter - Joystick::Width) / 2);
		}

		static constexpr uint8_t GetButtonStartX()
		{
			return OffsetX + ((Width - ButtonStart::Width) / 2);
		}

		static constexpr uint8_t GetButtonStartY()
		{
			return OffsetY + ((Height - ButtonStart::Height) / 4) - 1;
		}

		static constexpr uint8_t GetButtonsCenterY()
		{
			return OffsetY + ((Height - ButtonStart::Height) / 2) - 2;
		}

		static constexpr uint8_t GetButtonAX()
		{
			return GetButtonBX() + ButtonA::Width - 1;
		}

		static constexpr uint8_t GetButtonAY()
		{
			return GetButtonBY() + ButtonA::Height;
		}

		static constexpr uint8_t GetButtonBX()
		{
			return GetButtonsStartX();
		}

		static constexpr uint8_t GetButtonBY()
		{
			return GetButtonsCenterY() - 2;
		}

		static constexpr uint8_t GetButtonCLeftX()
		{
			return GetButtonAX() + (ButtonA::Width / 2) - 1;
		}

		static constexpr uint8_t GetButtonCUpDownX()
		{
			return GetButtonCLeftX() + ButtonC::Width;
		}

		static constexpr uint8_t GetButtonCDownY()
		{
			return GetButtonsCenterY();
		}

		static constexpr uint8_t GetButtonCUpY()
		{
			return GetButtonCDownY() - (2 * ButtonC::Width);
		}

		static constexpr uint8_t GetButtonCRightX()
		{
			return GetButtonCUpDownX() + (GetButtonCUpDownX() - GetButtonCLeftX());
		}

		static constexpr uint8_t GetButtonCLeftRightY()
		{
			return GetButtonCDownY() - ButtonC::Height;
		}

		static constexpr uint8_t GetIconX()
		{
			return Width - 1 - IconBitmapSprite::Width;
		}
		static constexpr uint8_t GetIconY()
		{
			return Height - 1 - IconBitmapSprite::Height;
		}
	};
}
#endif