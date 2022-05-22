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
	mButtonFont(font),
	mAARect(Vec2D::Zero, Vec2D::Zero),
	mButtonText(""), mIsActive(false),
	mAction(nullptr),
	buttonBase(),
	buttonHighlighted(),
	baseText(),
	highlightedText(){
}

void Button::InitButton(const Size& buttonSize, const std::string& text, Vec2D position)
{
	Vec2D topLeft(position.GetX() - buttonSize.width/2, position.GetY() - buttonSize.height/2);
	Vec2D bottomRight(position.GetX() + buttonSize.width/2, position.GetY() + buttonSize.height/2);

	mAARect = AARectangle(topLeft, bottomRight);
	mButtonText = text;

	mTextPosition = mButtonFont.GetDrawPosition(mButtonText, mAARect, FHA_Center, FVA_Middle);
};

void Button::Draw(Screen& screen){
	if(mIsActive){
		screen.Draw(mAARect, buttonHighlighted, true, buttonHighlighted, false);
		mButtonFont.DrawText(screen, mButtonText, mTextPosition, highlightedText, false, false);
	}else{
		screen.Draw(mAARect, buttonBase, true, buttonBase, false);
		mButtonFont.DrawText(screen, mButtonText, mTextPosition, baseText, false, false);
	}

}

void Button::ExecuteAction(){
	if(mAction){
		mAction();
	}
}

void Button::SetButtonColors(const Color& base, const Color& highlighted, const Color& baseText, const Color& highlightedText){
	this->buttonBase = base;
	this->buttonHighlighted = highlighted;
	this->baseText = baseText;
	this->highlightedText = highlightedText;
}

void Button::SetButtonActive(const bool& active){
	mIsActive = active;
}
