#include "ColorManipulation.h"

Color ModifyColorMultiply(const Color& inColor, const Color& modifier){

	float rVal = static_cast<float>(inColor.GetRed()) / 255.0f;
	float gVal = static_cast<float>(inColor.GetGreen()) / 255.0f;
	float bVal = static_cast<float>(inColor.GetBlue()) / 255.0f;
	float aVal = static_cast<float>(inColor.GetAlpha()) / 255.0f;

	uint8_t red = static_cast<uint8_t>(modifier.GetRed() * rVal);
	uint8_t green = static_cast<uint8_t>(modifier.GetGreen() * gVal);
	uint8_t blue = static_cast<uint8_t>(modifier.GetBlue() * bVal);
	uint8_t alpha = static_cast<uint8_t>(modifier.GetAlpha() * aVal);

	Color col(red, green, blue, alpha);
	return col;
}

Color ModifyColorInvert(const Color& inColor){
	uint8_t red = 255.0 - inColor.GetRed();
	uint8_t green = 255.0 - inColor.GetGreen();
	uint8_t blue = 255.0 - inColor.GetBlue();

	Color col(red, green, blue, inColor.GetAlpha());
	return col;
}


