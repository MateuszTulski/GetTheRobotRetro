#include <iostream>
#include "Color.h"
#include "ColorManipulation.h"

ColorManipulation::ColorManipulation() : mColor(), mModifier(COL_MULTIPLY)
{
	mColor = Color::White();
}

ColorManipulation::ColorManipulation(ColorModifier modifier, const Color& color) : mColor(color), mModifier(modifier)
{

}

void ColorManipulation::SetModifier(ColorModifier modifier, const Color& color)
{
	mModifier = modifier;
	mColor = color;
}

Color ColorManipulation::ModifyColor(const Color& inputColor) const
{
	switch(mModifier)
	{
	case COL_MULTIPLY:
		return ColorMultiply(inputColor);

	case COL_SCREEN:
		return ColorScreen(inputColor);

	case COL_DESATURATE:
		return ColorDesaturate(inputColor);
	}
	return inputColor;
}

Color ColorManipulation::ColorMultiply(const Color& inputColor) const
{
	float rVal = static_cast<float>(mColor.GetRed()) / 255.0f;
	float gVal = static_cast<float>(mColor.GetGreen()) / 255.0f;
	float bVal = static_cast<float>(mColor.GetBlue()) / 255.0f;
	float aVal = static_cast<float>(mColor.GetAlpha()) / 255.0f;

	uint8_t red = static_cast<uint8_t>(inputColor.GetRed() * rVal);
	uint8_t green = static_cast<uint8_t>(inputColor.GetGreen() * gVal);
	uint8_t blue = static_cast<uint8_t>(inputColor.GetBlue() * bVal);
	uint8_t alpha = static_cast<uint8_t>(inputColor.GetAlpha() * aVal);

	return Color(red, green, blue, alpha);
}

Color ColorManipulation::ColorScreen(const Color& inputColor) const
{
	return inputColor;
}

Color ColorManipulation::ColorDesaturate(const Color& inputColor) const
{
	return inputColor;
}


