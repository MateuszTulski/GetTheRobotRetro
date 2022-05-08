#include "Animation.h"
#include "Screen.h"
#include "App.h"

#include <cassert>


Animation::Animation() : Animation(DEFAULT_ANIMATINOS_FPS){

}

Animation::Animation(int speedInFrames) :
		mSpriteSheet(),
		mFramesNames(),
		mActualFrame(0),
		clipSpeedInFrames(speedInFrames),
		isPlaying(true),
		loopTime(true),
		playReverse(false){
}

Animation::Animation(const std::string& spriteFileName, int speedInFrames) : Animation(speedInFrames){

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

void Animation::Update(){

	if(App::Singleton().GetTime().GetActualFrame() % clipSpeedInFrames == 0)
	{
		ChangeAnimFrame();
	}
}

void Animation::Draw(Screen& screen, const Vec2D& pivotPoint){

	DrawFlipped(screen, pivotPoint, false, false);
}
void Animation::DrawFlipped(Screen& screen, const Vec2D& pivotPoint, bool flipHorizontal, bool flipVertical){

	if(mFramesNames.size() > 0){
		screen.DrawFlipped(mSpriteSheet, mFramesNames.at(mActualFrame), GetDrawPosition(pivotPoint), flipHorizontal, flipVertical);
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

void Animation::ChangeAnimFrame(){

	size_t frame {0};

	if(!playReverse)
	{
		frame = mActualFrame + 1;

		if(frame >= mFramesNames.size())
		{
			frame = 0;
		}
	}
	else
	{
		frame = mActualFrame - 1;

		if(frame < 0)
		{
			frame = mFramesNames.size() - 1;
		}
	}

	mActualFrame = static_cast<unsigned int>(frame);
}















