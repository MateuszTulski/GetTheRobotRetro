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
	BitmapFont();
	BitmapFont(unsigned int letterSpace, unsigned int wordsSpace);

	bool LoadFont(const std::string& fontName);
	Size GetTextSize(const std::string& text) const;
	Vec2D GetDrawPosition(const std::string& text, const AARectangle& rect, FontHorizontalAlign hAlign=FHA_Left, FontVerticalAlign vAlign=FVA_Top) const;

	void DrawText(Screen& screen, const std::string& text, const Vec2D& position, const Color& color = Color::White(), bool flipHorizontal=false, bool globalPosition=false);

	void SetFontHeight(const unsigned int& heightInPixels);

	inline const SpriteSheet& GetSpriteSheet() const {return mFontSheet;}
	inline unsigned int GetFontLetterSpace() const {return mLetterSpace;}
	inline unsigned int GetFontWordSpace() const {return mWordSpace;}

private:
	unsigned int mLetterSpace, mWordSpace, fontHeight;
	SpriteSheet mFontSheet;
	bool GetFontHeight(const std::string& fontName);
};


#endif /* SRC_GRAPHICS_BITMAPFONT_H_ */
