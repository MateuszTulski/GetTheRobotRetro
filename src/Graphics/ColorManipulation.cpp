#include "ColorManipulation.h"
#include <iostream>

ColorManipulation::ColorManipulation() : ColorManipulation(COL_MULTIPLY, Color().White())
{

}

ColorManipulation::ColorManipulation(ColorModifier modifier, const Color& color) : mModifier(modifier)
{
	mColor = color;
}

void ColorManipulation::ModifyColor(Color& inputColor)
{
	switch(mModifier)
	{
	case COL_MULTIPLY:
		ColorMultiply(inputColor);
		break;
	case COL_SCREEN:
		ColorScreen(inputColor);
		break;
	case COL_DESATURATE:
		ColorDesaturate(inputColor);
		break;
	}
}

void ColorManipulation::ColorMultiply(Color& inputColor)
{
	float rVal = static_cast<float>(mColor.GetRed()) / 255.0f;
	float gVal = static_cast<float>(mColor.GetGreen()) / 255.0f;
	float bVal = static_cast<float>(mColor.GetBlue()) / 255.0f;
	float aVal = static_cast<float>(mColor.GetAlpha()) / 255.0f;

	uint8_t red = static_cast<uint8_t>(inputColor.GetRed() * rVal);
	uint8_t green = static_cast<uint8_t>(inputColor.GetGreen() * gVal);
	uint8_t blue = static_cast<uint8_t>(inputColor.GetBlue() * bVal);
	uint8_t alpha = static_cast<uint8_t>(inputColor.GetAlpha() * aVal);

	inputColor = Color(red, green, blue, alpha);
}

void ColorManipulation::ColorScreen(Color& inputColor)
{

}

void ColorManipulation::ColorDesaturate(Color& inputColor)
{

}

