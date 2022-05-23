#ifndef SRC_GRAPHICS_COLORMANIPULATION_H_
#define SRC_GRAPHICS_COLORMANIPULATION_H_

#include "Color.h"

Color ModifyColorMultiply(const Color& inColor, const Color& modifier);
Color ModifyColorInvert(const Color& inColor);

#endif /* SRC_GRAPHICS_COLORMANIPULATION_H_ */
