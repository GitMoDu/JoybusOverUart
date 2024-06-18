// GCControllerDrawer.h

#ifndef _GC_CONTROLLER_DRAWER_h
#define _GC_CONTROLLER_DRAWER_h

#if defined(USE_CONTROLLER_DISPLAY)

#include <ArduinoGraphicsDrawer.h>
#include <GameCubeController.h>

#include "GCDrawAssets.h"

using namespace SpriteShaderEffect;
using namespace SpriteShader;
using namespace GCDrawAssets;


template<typename Layout>
class GCControllerDrawer : public ElementDrawer
{
private:
	enum class DrawElementsEnum : uint8_t
	{
		CopyState,
		A,
		B,
		X,
		Y,
		Start,
		DPadUp,
		DPadRight,
		DPadLeft,
		DPadDown,
		DPadCenter,
		ShoulderL,
		ShoulderR,
		TriggerL,
		TriggerR,
		Z,
		JoyLimits,
		JoyHead,
		JoyCLimits,
		JoyCNeck,
		JoyCHead,
		Icon,
		DrawElementsCount
	};

	static constexpr uint32_t DisconnectFlashDuration = 250000;

private:
	RgbColor Color{};

	BrightnessEffect<TransparentColorEffect<ButtonABitmapSprite>> ButtonASprite{};
	BrightnessEffect<TransparentColorEffect<ButtonBBitmapSprite>> ButtonBSprite{};
	BrightnessEffect<TransparentColorEffect<ButtonXBitmapSprite>> ButtonXSprite{};
	BrightnessEffect<TransparentColorEffect<ButtonYBitmapSprite>> ButtonYSprite{};
	BrightnessEffect<TransparentColorEffect<ButtonStartBitmapSprite>> ButtonStartSprite{};
	BrightnessEffect<DPadUpBitmapSprite> DPadUpSprite{};
	BrightnessEffect<DPadLeftBitmapSprite> DPadLeftSprite{};
	BrightnessEffect<DPadCenterBitmapSprite> DPadCenterSprite{};
	BrightnessEffect<SingleColorShader<ButtonZBitmaskSprite>> ButtonZSprite{};

	//BrightnessEffect<SingleColorShader<ShoulderLBitmaskSprite>> ShoulderLSprite{};
	//SingleColorShader<JoystickNeckBitmaskSprite> JoystickNeckSprite{};
	BrightnessEffect<TransparentColorEffect<JoystickBitmapSprite>> JoystickSprite{};
	BrightnessEffect<TransparentColorEffect<JoyCBitmapSprite>> JoyCSprite{};
	TransparentColorEffect<IconBitmapSprite> IconSprite{};

private:
	GameCubeController::state_data_t State{};

private:
	const GameCubeController::state_data_t& SourceState;

public:
	GCControllerDrawer(IFrameBuffer* frame,
		const GameCubeController::state_data_t& controllerState)
		: ElementDrawer(frame, (uint8_t)DrawElementsEnum::DrawElementsCount)
		, SourceState(controllerState)
	{
		Color.FromRGB32(Pallete::PurpleRGB);
		ButtonZSprite.SetColor(Color);

		Color.FromRGB32(Pallete::Black);
		ButtonASprite.SetTransparentColor(Color);
		ButtonBSprite.SetTransparentColor(Color);
		ButtonXSprite.SetTransparentColor(Color);
		ButtonYSprite.SetTransparentColor(Color);
		ButtonStartSprite.SetTransparentColor(Color);
		JoystickSprite.SetTransparentColor(Color);
		IconSprite.SetTransparentColor(Color);

		Color.FromRGB32(Pallete::WhitePadRGB);
	}

	virtual void DrawCall(DrawState* drawState) final
	{
		switch (drawState->ElementIndex)
		{
		case (uint8_t)DrawElementsEnum::CopyState:
			State.CopyFrom(SourceState);
			break;
		case (uint8_t)DrawElementsEnum::A:
			if (!State.Connected)
			{
				ButtonASprite.SetBrightness(Pallete::DisconnectTint);
				SpriteRenderer::Draw(Frame, &ButtonASprite, Layout::GetButtonAX(), Layout::GetButtonAY());
			}
			else if (State.Button<ButtonsEnum::A>())
			{
				ButtonASprite.SetBrightness(Pallete::HighlightTint);
				SpriteRenderer::Draw(Frame, &ButtonASprite, Layout::GetButtonAX(), Layout::GetButtonAY() + 1);
			}
			else
			{
				ButtonASprite.SetBrightness(0);
				SpriteRenderer::Draw(Frame, &ButtonASprite, Layout::GetButtonAX(), Layout::GetButtonAY());
			}
			break;
		case (uint8_t)DrawElementsEnum::B:
			if (!State.Connected)
			{
				ButtonBSprite.SetBrightness(Pallete::DisconnectTint);
				SpriteRenderer::Draw(Frame, &ButtonBSprite, Layout::GetButtonBX(), Layout::GetButtonBY());
			}
			else if (State.Button<ButtonsEnum::B>())
			{
				ButtonBSprite.SetBrightness(Pallete::HighlightTint);
				SpriteRenderer::Draw(Frame, &ButtonBSprite, Layout::GetButtonBX(), Layout::GetButtonBY() + 1);
			}
			else
			{
				ButtonBSprite.SetBrightness(0);
				SpriteRenderer::Draw(Frame, &ButtonBSprite, Layout::GetButtonBX(), Layout::GetButtonBY());
			}
			break;

		case (uint8_t)DrawElementsEnum::X:
			if (!State.Connected)
			{
				ButtonXSprite.SetBrightness(Pallete::DisconnectTintSoft);
				SpriteRenderer::Draw(Frame, &ButtonXSprite, Layout::GetButtonXX(), Layout::GetButtonXY());
			}
			else if (State.Button<ButtonsEnum::X>())
			{
				ButtonXSprite.SetBrightness(Pallete::HighlightTint);
				SpriteRenderer::Draw(Frame, &ButtonXSprite, Layout::GetButtonXX(), Layout::GetButtonXY() + 1);
			}
			else
			{
				ButtonXSprite.SetBrightness(0);
				SpriteRenderer::Draw(Frame, &ButtonXSprite, Layout::GetButtonXX(), Layout::GetButtonXY());
			}
			break;
		case (uint8_t)DrawElementsEnum::Y:
			if (!State.Connected)
			{
				ButtonYSprite.SetBrightness(Pallete::DisconnectTintSoft);
				SpriteRenderer::Draw(Frame, &ButtonYSprite, Layout::GetButtonYX(), Layout::GetButtonYY());
			}
			else if (State.Button<ButtonsEnum::Y>())
			{
				ButtonYSprite.SetBrightness(Pallete::HighlightTint);
				SpriteRenderer::Draw(Frame, &ButtonYSprite, Layout::GetButtonYX(), Layout::GetButtonYY() + 1);
			}
			else
			{
				ButtonYSprite.SetBrightness(0);
				SpriteRenderer::Draw(Frame, &ButtonYSprite, Layout::GetButtonYX(), Layout::GetButtonYY());
			}
			break;
		case (uint8_t)DrawElementsEnum::Start:
			if (!State.Connected)
			{
				ButtonStartSprite.SetBrightness(Pallete::DisconnectTint);
				SpriteRenderer::Draw(Frame, &ButtonStartSprite, Layout::GetButtonStartX(), Layout::GetButtonStartY());
			}
			else if (State.Button<ButtonsEnum::Start>())
			{
				ButtonStartSprite.SetBrightness(Pallete::HighlightTint);
				SpriteRenderer::Draw(Frame, &ButtonStartSprite, Layout::GetButtonStartX(), Layout::GetButtonStartY() + 1);
			}
			else
			{
				ButtonStartSprite.SetBrightness(0);
				SpriteRenderer::Draw(Frame, &ButtonStartSprite, Layout::GetButtonStartX(), Layout::GetButtonStartY());
			}
			break;
		case (uint8_t)DrawElementsEnum::DPadUp:
			if (!State.Connected)
			{
				DPadUpSprite.SetBrightness(Pallete::DisconnectTintSoft);
				SpriteRenderer::Draw(Frame, &DPadUpSprite, Layout::GetDPadX() + DPadLeftBitmapSprite::Width, Layout::GetDPadY());
			}
			else if (State.Button<ButtonsEnum::Up>())
			{
				DPadUpSprite.SetBrightness(Pallete::HighlightTint);
				SpriteRenderer::Draw(Frame, &DPadUpSprite, Layout::GetDPadX() + DPadLeftBitmapSprite::Width, Layout::GetDPadY() + 1);
			}
			else
			{
				DPadUpSprite.SetBrightness(0);
				SpriteRenderer::Draw(Frame, &DPadUpSprite, Layout::GetDPadX() + DPadLeftBitmapSprite::Width, Layout::GetDPadY());
			}
			break;
		case (uint8_t)DrawElementsEnum::DPadLeft:
			if (!State.Connected)
			{
				DPadLeftSprite.SetBrightness(Pallete::DisconnectTintSoft);
				SpriteRenderer::Draw(Frame, &DPadLeftSprite, Layout::GetDPadX(), Layout::GetDPadY() + DPadUpBitmapSprite::Height);
			}
			else if (State.Button<ButtonsEnum::Left>())
			{
				DPadLeftSprite.SetBrightness(Pallete::HighlightTint);
				SpriteRenderer::Draw(Frame, &DPadLeftSprite, Layout::GetDPadX(), Layout::GetDPadY() + DPadUpBitmapSprite::Height + 1);
			}
			else
			{
				DPadLeftSprite.SetBrightness(0);
				SpriteRenderer::Draw(Frame, &DPadLeftSprite, Layout::GetDPadX(), Layout::GetDPadY() + DPadUpBitmapSprite::Height);
			}
			break;
		case (uint8_t)DrawElementsEnum::DPadRight:
			if (!State.Connected)
			{
				DPadLeftSprite.SetBrightness(Pallete::DisconnectTintSoft);
				SpriteRenderer::TransformDraw<InvertTransform::InvertX<DPadLeftBitmapSprite::Width, DPadLeftBitmapSprite::Height>>(Frame, &DPadLeftSprite, Layout::GetDPadX() + DPadLeftBitmapSprite::Width + DPadCenterBitmapSprite::Width, Layout::GetDPadY() + DPadLeftBitmapSprite::Height, 0);
			}
			else if (State.Button<ButtonsEnum::Right>())
			{
				DPadLeftSprite.SetBrightness(Pallete::HighlightTint);
				SpriteRenderer::TransformDraw<InvertTransform::InvertX<DPadLeftBitmapSprite::Width, DPadLeftBitmapSprite::Height>>(Frame, &DPadLeftSprite, Layout::GetDPadX() + DPadLeftBitmapSprite::Width + DPadCenterBitmapSprite::Width, Layout::GetDPadY() + DPadLeftBitmapSprite::Height + 1, 0);
			}
			else
			{
				DPadLeftSprite.SetBrightness(0);
				SpriteRenderer::TransformDraw<InvertTransform::InvertX<DPadLeftBitmapSprite::Width, DPadLeftBitmapSprite::Height>>(Frame, &DPadLeftSprite, Layout::GetDPadX() + DPadLeftBitmapSprite::Width + DPadCenterBitmapSprite::Width, Layout::GetDPadY() + DPadLeftBitmapSprite::Height, 0);
			}
			break;
		case (uint8_t)DrawElementsEnum::DPadDown:
			if (!State.Connected)
			{
				DPadUpSprite.SetBrightness(Pallete::DisconnectTintSoft);
				SpriteRenderer::TransformDraw<InvertTransform::InvertY<DPadUp::Width, DPadUpBitmapSprite::Height>>(Frame, &DPadUpSprite, Layout::GetDPadX() + DPadLeftBitmapSprite::Width, Layout::GetDPadY() + DPadUpBitmapSprite::Height + DPadCenterBitmapSprite::Height, 0);
			}
			else if (State.Button<ButtonsEnum::Down>())
			{
				DPadUpSprite.SetBrightness(Pallete::HighlightTint);
				SpriteRenderer::TransformDraw<InvertTransform::InvertY<DPadUp::Width, DPadUpBitmapSprite::Height>>(Frame, &DPadUpSprite, Layout::GetDPadX() + DPadLeftBitmapSprite::Width, Layout::GetDPadY() + DPadUpBitmapSprite::Height + DPadCenterBitmapSprite::Height - 1, 0);
			}
			else
			{
				DPadUpSprite.SetBrightness(0);
				SpriteRenderer::TransformDraw<InvertTransform::InvertY<DPadUp::Width, DPadUpBitmapSprite::Height>>(Frame, &DPadUpSprite, Layout::GetDPadX() + DPadLeftBitmapSprite::Width, Layout::GetDPadY() + DPadUpBitmapSprite::Height + DPadCenterBitmapSprite::Height, 0);
			}
			break;
		case (uint8_t)DrawElementsEnum::DPadCenter:
			if (State.Connected)
			{
				DPadCenterSprite.SetBrightness(0);
				SpriteRenderer::Draw(Frame, &DPadCenterSprite, Layout::GetDPadX() + DPadLeftBitmapSprite::Width, Layout::GetDPadY() + DPadUpBitmapSprite::Height);
			}
			else
			{
				DPadCenterSprite.SetBrightness(Pallete::DisconnectTintSoft);
				SpriteRenderer::Draw(Frame, &DPadCenterSprite, Layout::GetDPadX() + DPadLeftBitmapSprite::Width, Layout::GetDPadY() + DPadUpBitmapSprite::Height);
			}
			break;
		case (uint8_t)DrawElementsEnum::ShoulderL:
			if (State.Connected)
			{
				if (State.Button<ButtonsEnum::L>())
				{
					Color.FromRGB32(Pallete::WhitePadRGB);
					Frame->Rectangle(Color, Layout::GetLX(), Layout::GetLRY(), Layout::GetLX() + Layout::GetLRWidth(), Layout::GetLRY() + Layout::GetLRHeight());
					Frame->RectangleFill(Color, Layout::GetLX() + 1, Layout::GetLRY() + 1, Layout::GetLX() + 1 + Layout::GetLRWidth(UINT8_MAX), Layout::GetLRY() + Layout::GetLRInnerHeight());
				}
				else
				{
					Color.FromRGB32(Pallete::GrayPadRGB);
					Frame->Rectangle(Color, Layout::GetLX(), Layout::GetLRY(), Layout::GetLX() + Layout::GetLRWidth(), Layout::GetLRY() + Layout::GetLRHeight());
					Color.FromRGB32(Pallete::WhitePadRGB);
					Frame->RectangleFill(Color, Layout::GetLX() + 1, Layout::GetLRY() + 1, Layout::GetLX() + 1 + Layout::GetLRWidth(State.SliderLeft), Layout::GetLRY() + Layout::GetLRInnerHeight());
				}
			}
			else
			{
				Color.FromRGB32(Pallete::GrayPadRGB);
				Frame->Rectangle(Color, Layout::GetLX(), Layout::GetLRY(), Layout::GetLX() + Layout::GetLRWidth(), Layout::GetLRY() + Layout::GetLRHeight());
			}
			break;
		case (uint8_t)DrawElementsEnum::ShoulderR:
			if (State.Connected)
			{
				if (State.Button<ButtonsEnum::R>())
				{
					Color.FromRGB32(Pallete::WhitePadRGB);
					Frame->Rectangle(Color, Layout::GetRX(), Layout::GetLRY(), Layout::GetRX() + Layout::GetLRWidth(), Layout::GetLRY() + Layout::GetLRHeight());
					Frame->RectangleFill(Color, Layout::GetRX() + 1, Layout::GetLRY() + 1, Layout::GetRX() + 1 + Layout::GetLRWidth(UINT8_MAX), Layout::GetLRY() + Layout::GetLRInnerHeight());
				}
				else
				{
					Color.FromRGB32(Pallete::GrayPadRGB);
					Frame->Rectangle(Color, Layout::GetRX(), Layout::GetLRY(), Layout::GetRX() + Layout::GetLRWidth(), Layout::GetLRY() + Layout::GetLRHeight());
					Color.FromRGB32(Pallete::WhitePadRGB);
					Frame->RectangleFill(Color, Layout::GetRX() +Layout::GetLRWidth(UINT8_MAX) - Layout::GetLRWidth(State.SliderRight), Layout::GetLRY() + 1, Layout::GetRX() + Layout::GetLRWidth(UINT8_MAX), Layout::GetLRY() + Layout::GetLRInnerHeight());
				}
			}
			else
			{
				Color.FromRGB32(Pallete::GrayPadRGB);
				Frame->Rectangle(Color, Layout::GetRX(), Layout::GetLRY(), Layout::GetRX() + Layout::GetLRWidth(), Layout::GetLRY() + Layout::GetLRHeight());
			}
			break;
		case (uint8_t)DrawElementsEnum::Z:
			if (!State.Connected)
			{
				ButtonZSprite.SetBrightness(Pallete::DisconnectTintSoft);
				SpriteRenderer::Draw(Frame, &ButtonZSprite, Layout::GetZX(), Layout::GetZY());
			}
			else if (State.Button<ButtonsEnum::Z>())
			{
				ButtonZSprite.SetBrightness(Pallete::HighlightTintSoft);
				SpriteRenderer::Draw(Frame, &ButtonZSprite, Layout::GetZX(), Layout::GetZY() + 1);
			}
			else
			{
				ButtonZSprite.SetBrightness(0);
				SpriteRenderer::Draw(Frame, &ButtonZSprite, Layout::GetZX(), Layout::GetZY());
			}
			break;
		case (uint8_t)DrawElementsEnum::JoyLimits:
			if (State.Connected)
			{
				Color.FromRGB32(Pallete::WhitePadRGB);
			}
			else
			{
				Color.FromRGB32(Pallete::WhiteDeepRGB);
			}
			DrawOctagon<Layout::GetJoyLimitsX(), Layout::GetJoyLimitsY(), JoyLimits::Diameter, JoyLimits::Octshift>(Color);
			break;
		case (uint8_t)DrawElementsEnum::JoyHead:
			DrawJoyHead();
			break;
		case (uint8_t)DrawElementsEnum::JoyCLimits:
			Color.FromRGB32(Pallete::YellowRGB);
			if (State.Connected)
			{
				Color.FromRGB32(Pallete::YellowRGB);
			}
			else
			{
				Color.FromRGB32(Pallete::YellowDarkRGB);
			}
			DrawOctagon<Layout::GetJoyCLimitsX(), Layout::GetJoyCLimitsY(), JoyCLimits::Diameter, JoyCLimits::Octshift>(Color);
			break;

		case (uint8_t)DrawElementsEnum::JoyCHead:
			DrawJoyCHead();
			break;
		case (uint8_t)DrawElementsEnum::Icon:
			DrawIcon(drawState->FrameTime);
			break;
		default:
			break;
		}
	}

private:
	void DrawIcon(const uint32_t frameTime)
	{
		const uint32_t elapsed = frameTime % DisconnectFlashDuration;
		const bool odd = elapsed > (DisconnectFlashDuration / 2);
		if (State.Connected
			|| odd)
		{
			SpriteRenderer::Draw(Frame, &IconSprite,
				Layout::GetIconX(),
				Layout::GetIconY());
		}
	}

	template<const uint8_t x1,
		const uint8_t y1,
		const uint8_t diameter,
		const int8_t octagonalShift>
	void DrawOctagon(const RgbColor& color)
	{
		constexpr uint8_t x2 = x1 + diameter;
		constexpr uint8_t y2 = y1 + diameter;
		constexpr uint8_t quarter = diameter / 4;

		constexpr uint8_t xCenter = ((uint16_t)x1 + x2 + 0) / 2;
		constexpr uint8_t yCenter = ((uint16_t)y1 + y2 + 1) / 2;
		constexpr uint8_t octshift = quarter - octagonalShift;
		constexpr uint8_t even = 1 * (octshift % 2) != 0;

		Frame->Line(color,
			x1,
			yCenter,
			x1 + octshift,
			y1 + octshift);

		Frame->Line(color,
			x1,
			yCenter,
			x1 + octshift,
			y2 - 1 - octshift);

		Frame->Line(color,
			x1 + octshift,
			y1 + octshift,
			xCenter + even,
			y1);

		Frame->Line(color,
			x1 + octshift,
			y2 - 1 - octshift,
			xCenter + even,
			y2 - 1);

		Frame->Line(color,
			xCenter + even,
			y1,
			x2 - 1 - octshift,
			y1 + octshift - 1
		);

		Frame->Line(color,
			xCenter + even,
			y2 - 1,
			x2 - 1 - octshift,
			y2 - octshift
		);

		Frame->Line(color,
			x2 - 1 - octshift,
			y1 + octshift,
			x2 - 1,
			yCenter
		);

		Frame->Line(color,
			x2 - 1 - octshift,
			y2 - octshift,
			x2 - 1,
			yCenter
		);
	}

	void DrawJoyCHead()
	{
		if (State.Connected)
		{
			int8_t dx = 0;
			int8_t dy = 0;
			if (State.JoystickCX >= 0)
			{
				dx = ((int16_t)State.JoystickCX * Layout::GetJoystickCScale()) / INT8_MAX;
				if (dx > Layout::GetJoystickCScale())
				{
					dx = Layout::GetJoystickCScale();
				}
			}
			else
			{
				dx = -((int16_t)State.JoystickCX * Layout::GetJoystickCScale()) / INT8_MIN;
				if (-dx > (int8_t)(Layout::GetJoystickCScale()))
				{
					dx = -(int8_t)(Layout::GetJoystickCScale());
				}
			}
			if (State.JoystickCX >= 0)
			{
				dy = ((int16_t)State.JoystickCY * Layout::GetJoystickCScale()) / INT8_MAX;
				if (dy > Layout::GetJoystickCScale())
				{
					dy = Layout::GetJoystickCScale();
				}
			}
			else
			{
				dy = -((int16_t)State.JoystickCY * Layout::GetJoystickCScale()) / INT8_MIN;
				if (-dy > (int8_t)(Layout::GetJoystickCScale()))
				{
					dy = -(int8_t)(Layout::GetJoystickCScale());
				}
			}

			JoyCSprite.SetBrightness(0);
			SpriteRenderer::Draw(Frame, &JoyCSprite, Layout::GetJoyCHeadX() + dx, Layout::GetJoyCHeadY() - dy);
		}
		else
		{
			JoyCSprite.SetBrightness(Pallete::DisconnectTint);
			SpriteRenderer::Draw(Frame, &JoyCSprite, Layout::GetJoyCHeadX(), Layout::GetJoyCHeadY());
		}
	}
	void DrawJoyHead()
	{
		if (State.Connected)
		{
			int8_t dx = 0;
			int8_t dy = 0;
			if (State.JoystickX >= 0)
			{
				dx = ((int16_t)State.JoystickX * Layout::GetJoystickScale()) / INT8_MAX;
				if (dx > Layout::GetJoystickScale())
				{
					dx = Layout::GetJoystickScale();
				}
			}
			else
			{
				dx = -((int16_t)State.JoystickX * Layout::GetJoystickScale()) / INT8_MIN;
				if (-dx > (int8_t)(Layout::GetJoystickScale()))
				{
					dx = -(int8_t)(Layout::GetJoystickScale());
				}
			}
			if (State.JoystickX >= 0)
			{
				dy = ((int16_t)State.JoystickY * Layout::GetJoystickScale()) / INT8_MAX;
				if (dy > Layout::GetJoystickScale())
				{
					dy = Layout::GetJoystickScale();
				}
			}
			else
			{
				dy = -((int16_t)State.JoystickY * Layout::GetJoystickScale()) / INT8_MIN;
				if (-dy > (int8_t)(Layout::GetJoystickScale()))
				{
					dy = -(int8_t)(Layout::GetJoystickScale());
				}
			}

			JoystickSprite.SetBrightness(0);
			SpriteRenderer::Draw(Frame, &JoystickSprite, Layout::GetJoyHeadX() + dx, Layout::GetJoyHeadY() - dy);
		}
		else
		{
			JoystickSprite.SetBrightness(Pallete::DisconnectTint);
			SpriteRenderer::Draw(Frame, &JoystickSprite, Layout::GetJoyHeadX(), Layout::GetJoyHeadY());
		}
	}
};
#endif
#endif