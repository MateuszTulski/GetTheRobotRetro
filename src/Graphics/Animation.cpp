#include "Animation.h"
#include "Screen.h"
#include <cassert>


Animation::Animation() : Animation(DEFAULT_ANIMATINOS_FPS){

}

Animation::Animation(float fps) : mSpriteSheet(), mFramesNames(), mActualFrame(0), mFrameRate(fps), isPlaying(true), loopTime(true), playReverse(false){

}

Animation::Animation(const std::string& spriteFileName, float fps) : Animation(fps){

	assert(LoadSprite(spriteFileName) && "Animation sprite couldn't be loaded");
}

bool Animation::LoadSprite(const std::string& name){

	if(mSpriteSheet.LoadSprite("Animations/" + name))
	{
		mFramesNames = mSpriteSheet.GetSpritestNames();
		return true;
	}
	return false;
}

void Animation::Update(uint32_t deltaTime){

}

void Animation::Draw(Screen& screen, const Vec2D& pivotPoint){

	if(mFramesNames.size() > 0)
	{
		screen.Draw(mSpriteSheet, mFramesNames.at(0), GetDrawPosition(pivotPoint));
	}
}

Vec2D Animation::GetDrawPosition(const Vec2D& pivotPoint){

	Vec2D drawPosition;

	float spriteHeight = mSpriteSheet.GetSpriteCoordinates(mFramesNames.at(mActualFrame)).height;
	float spriteWidth = mSpriteSheet.GetSpriteCoordinates(mFramesNames.at(mActualFrame)).width;

	switch(mAlign.vertical)
	{
		case(AnimVerticalAlign::Top):
			drawPosition.SetY(pivotPoint.GetY());
			break;

		case(AnimVerticalAlign::Center):
			drawPosition.SetY(pivotPoint.GetY() - spriteHeight/2);
			break;

		case(AnimVerticalAlign::Bottom):
			drawPosition.SetY(pivotPoint.GetY() - spriteHeight);
			break;
		default:
			drawPosition.SetY(pivotPoint.GetY());
	}

	switch(mAlign.horizontal)
	{
		case(AnimHorizontalAlign::Left):
			drawPosition.SetX(pivotPoint.GetX());
			break;

		case(AnimHorizontalAlign::Center):
			drawPosition.SetX(pivotPoint.GetX() - spriteWidth/2);
			break;

		case(AnimHorizontalAlign::Right):
			drawPosition.SetX(pivotPoint.GetX() - spriteWidth);
			break;
		default:
			drawPosition.SetX(pivotPoint.GetX());
	}

	return drawPosition;
}

