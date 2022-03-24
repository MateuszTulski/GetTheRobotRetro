#ifndef SRC_GRAPHICS_BITMAPFONT_H_
#define SRC_GRAPHICS_BITMAPFONT_H_

#include "SpriteSheet.h"
#include "Utils.h"

class Vec2D;
class AARectangle;

enum FontVerticalAlign{
	FVA_Top = 0,
	FVA_Middle,
	FVA_Bottom
};

enum FontHorizontalAlign{
	FHA_Left = 0,
	FHA_Center,
	FHA_Right
};

class BitmapFont {
public:
	BitmapFont(unsigned int letterSpace = 2, unsigned int wordSpace = 5);

	bool LoadFont(const std::string& fontName);
	Size GetTextSize(const std::string& text) const;
	Vec2D GetDrawPosition(const std::string&text, const AARectangle& rect, FontHorizontalAlign hAlign = FHA_Left, FontVerticalAlign vAlign = FVA_Top);

	inline SpriteSheet GetSpriteSheet() const {return mFontSheet;}
	inline unsigned int GetFontLetterSpace() const {return mLetterSpace;}
	inline unsigned int GetFontWordSpace() const {return mWordSpace;}

private:
	unsigned int mLetterSpace = 2, mWordSpace = 5;
	SpriteSheet mFontSheet;
};



#endif /* SRC_GRAPHICS_BITMAPFONT_H_ */
