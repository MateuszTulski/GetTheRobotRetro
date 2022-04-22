#include "App.h"
#include "Utils.h"
#include "Button.h"
#include "BitmapFont.h"
#include "Screen.h"
#include <iostream>
#include "ColorManipulation.h"

Button::Button() : Button(App::Singleton().GetAppFont()){
}

Button::Button(const BitmapFont& font):
	mButtonFont(font), mAARect(Vec2D::Zero, Vec2D::Zero), mButtonText(""), mIsActive(false), mAction(nullptr), mBaseColor(), mHighlightColor(){
}

void Button::InitButton(const Size& buttonSize, const std::string& text, Vec2D position)
{
	Vec2D topLeft(position.GetX() - buttonSize.width/2, position.GetY() - buttonSize.height/2);
	Vec2D bottomRight(position.GetX() + buttonSize.width/2, position.GetY() + buttonSize.height/2);

	mAARect = AARectangle(topLeft, bottomRight);
	mButtonText = text;

	mTextPosition = mButtonFont.GetDrawPosition(mButtonText, mAARect, FHA_Center, FVA_Middle);
	mBaseColor.SetModifier(COL_MULTIPLY, Color().White());
};

void Button::Draw(Screen& screen)
{
	screen.Draw(mAARect, mBaseColor.GetModifierColor(), mIsActive, mHighlightColor.GetModifierColor());

	if(mIsActive){
		screen.Draw(mButtonFont, mButtonText, mTextPosition, mHighlightedTextColor);
	}else{
		screen.Draw(mButtonFont, mButtonText, mTextPosition, mBaseColor);
	}

}

void Button::ExecuteAction()
{
	if(mAction)
	{
		mAction();
	}
}

void Button::SetHighlitColor(const Color& color){

	mHighlightColor.SetModifier(COL_MULTIPLY, color);
	mHighlightedTextColor.SetModifier(COL_MULTIPLY, Color(10, 10, 10, 255));
}

void Button::SetButtonActive(const bool& active)
{
	mIsActive = active;
}
