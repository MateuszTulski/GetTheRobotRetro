#include "UIDynamicText.h"
#include "Utils.h"

UIDynamicText::UIDynamicText() :
		BitmapFont(),
		mOverlayColor(Color::White()),
		activeText(std::string("")){
}

UIDynamicText::UIDynamicText(GetValue val) :
		BitmapFont(),
		mOverlayColor(Color::White()),
		mScreenPosition(Vec2D::Zero),
		getValueFunc(val),
		activeText(std::string("")){
}

UIDynamicText::UIDynamicText(const UIDynamicText& other) :
		BitmapFont(other),
		getValueFunc(other.getValueFunc){
}

UIDynamicText& UIDynamicText::operator=(const UIDynamicText& other){
	if(this != &other){
		BitmapFont::operator=(other);
		mOverlayColor = other.mOverlayColor;
		mScreenPosition = other.mScreenPosition;
		getValueFunc = other.getValueFunc;
		activeText = other.activeText;
	}

	return *this;
}

void UIDynamicText::SetScreenPosition(uint32_t screenX, uint32_t screenY){
	mScreenPosition = Vec2D(screenX, screenY);
}

void UIDynamicText::DrawDynamicText(Screen& screen){
	UpdateText(getValueFunc());
	Vec2D drawPosition = Vec2D(mScreenPosition.GetX()-textSize.width/2, mScreenPosition.GetY()-textSize.height/2);
	BitmapFont::DrawText(screen, activeText, drawPosition, mOverlayColor, FLIP_HORIZONTAL, GLOBAL_POSITION);
}

void UIDynamicText::UpdateText(const std::string& text){
	if(activeText != text){
		activeText = text;
		textSize = GetTextSize(text);
	}
}
