#ifndef SRC_GRAPHICS_COLORMANIPULATION_H_
#define SRC_GRAPHICS_COLORMANIPULATION_H_

#include "Color.h"
#include "Utils.h"
#include <stdint.h>

enum ColorModifier{
	COL_MULTIPLY = 0,
	COL_SCREEN,
	COL_DESATURATE
};

class ColorManipulation
{
public:
	ColorManipulation();
	ColorManipulation(ColorModifier modifier, const Color& color);

	void ModifyColor(Color& inputColor);

private:
	void ColorMultiply(Color& inputColor);
	void ColorScreen(Color& inputColor);
	void ColorDesaturate(Color& inputColor);

	ColorModifier mModifier;
	Color mColor;
};


#endif /* SRC_GRAPHICS_COLORMANIPULATION_H_ */
