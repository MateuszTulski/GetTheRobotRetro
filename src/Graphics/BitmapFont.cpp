#include "BitmapFont.h"
#include "AARectangle.h"
#include "App.h"
#include <fstream>
#include <sstream>

BitmapFont::BitmapFont() : BitmapFont(1, 7){}

BitmapFont::BitmapFont(unsigned int letterSpace, unsigned int wordSpace) : mLetterSpace(letterSpace), mWordSpace(wordSpace), fontHeight(0){
}

bool BitmapFont::LoadFont(const std::string& fontName){

	bool fontLoaded = mFontSheet.LoadSprite(fontName);

	return fontLoaded && GetFontHeight(fontName);
}

Size BitmapFont::GetTextSize(const std::string& text) const{

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

Vec2D BitmapFont::GetDrawPosition(const std::string&text, const AARectangle& rect, FontHorizontalAlign hAlign, FontVerticalAlign vAlign) const{

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

void BitmapFont::SetFontHeight(const unsigned int& heightInPixels){

	float scale = heightInPixels / static_cast<float>(fontHeight);

	mFontSheet.ScaleSpriteSheet(scale, scale, false);
}

bool BitmapFont::GetFontHeight(const std::string& fontName){

	std::string fontPath(App::Singleton().GetBasePath() + std::string("Assets/") + fontName + ".txt");

	std::fstream fs;
	fs.open(fontPath);

	if(!fs.is_open()){
		return false;
	}

	std::string line;
	while(std::getline(fs, line)){

		std::string command;
		std::stringstream ss;
		ss << line;

		bool getValueFromNextIteration {false};

		while(ss >> command){
			if(command == ":fontHeight")
			{
				getValueFromNextIteration = true;
			}
			else if(getValueFromNextIteration)
			{
				fontHeight = std::stoi(command);
				return true;
			}
		}
	}

	return true;
}
