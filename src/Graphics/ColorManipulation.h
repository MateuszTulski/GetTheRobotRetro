#ifndef SRC_GRAPHICS_COLORMANIPULATION_H_
#define SRC_GRAPHICS_COLORMANIPULATION_H_

#include "Utils.h"
#include <stdint.h>

class Color;

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
	~ColorManipulation(){}

	void SetModifier(ColorModifier modifier, const Color& color);
	inline Color GetModifierColor() const {return mColor;}

	Color ModifyColor(const Color& inputColor) const;

	static ColorManipulation NoColorManipulation() {
		static ColorManipulation manip;
		return manip;
	}

private:
	Color mColor;
	ColorModifier mModifier;

	Color ColorMultiply(const Color& inputColor) const;
	Color ColorScreen(const Color& inputColor) const;
	Color ColorDesaturate(const Color& inputColor) const;
};


#endif /* SRC_GRAPHICS_COLORMANIPULATION_H_ */
