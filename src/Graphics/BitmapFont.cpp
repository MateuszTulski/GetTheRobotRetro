#include "BitmapFont.h"
#include "AARectangle.h"

BitmapFont::BitmapFont() : BitmapFont(1, 7){}

BitmapFont::BitmapFont(unsigned int letterSpace, unsigned int wordSpace) : mLetterSpace(letterSpace), mWordSpace(wordSpace){
}

bool BitmapFont::LoadFont(const std::string& fontName)
{
	return mFontSheet.LoadSprite(fontName);
}

Size BitmapFont::GetTextSize(const std::string& text) const
{
	Size textSize;

	for(char c : text){

		if(c == ' ')
		{
			textSize.width += GetFontWordSpace();
			continue;
		}

		Sprite sprite = mFontSheet.GetSpriteCoordinates(std::string("")+c);
		textSize.height = textSize.height < sprite.height ? sprite.height : textSize.height;

		textSize.width += sprite.width;				// Add word width
		textSize.width += GetFontLetterSpace();		// Add letter space
	}

	return textSize;
}

Vec2D BitmapFont::GetDrawPosition(const std::string&text, const AARectangle& rect, FontHorizontalAlign hAlign, FontVerticalAlign vAlign) const
{
	Size textSize = GetTextSize(text);

	// For default set top left corner
	unsigned int x = 0;
	unsigned int y = 0;

	if(hAlign == FHA_Center)
	{
		x = rect.GetCenterPoint().GetX() - textSize.width/2;
	}
	else if (hAlign == FHA_Right)
	{
		x = rect.GetBottomRight().GetX() - textSize.width;
	}

	if(vAlign == FVA_Middle)
	{
		y = rect.GetCenterPoint().GetY() - textSize.height/2;
	}
	else if (vAlign == FVA_Bottom)
	{
		y = rect.GetBottomRight().GetY() - textSize.height;
	}


	return Vec2D(x, y);
}

