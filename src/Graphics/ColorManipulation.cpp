#include "ColorManipulation.h"

Color ModifyColorMultiply(const Color& outColor, const Color& modifier){

	float rVal = static_cast<float>(outColor.GetRed()) / 255.0f;
	float gVal = static_cast<float>(outColor.GetGreen()) / 255.0f;
	float bVal = static_cast<float>(outColor.GetBlue()) / 255.0f;
	float aVal = static_cast<float>(outColor.GetAlpha()) / 255.0f;

	uint8_t red = static_cast<uint8_t>(modifier.GetRed() * rVal);
	uint8_t green = static_cast<uint8_t>(modifier.GetGreen() * gVal);
	uint8_t blue = static_cast<uint8_t>(modifier.GetBlue() * bVal);
	uint8_t alpha = static_cast<uint8_t>(modifier.GetAlpha() * aVal);

	Color col(red, green, blue, alpha);
	return col;
}



