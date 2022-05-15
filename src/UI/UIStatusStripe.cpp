#include "UIStatusStripe.h"
#include "ColorManipulation.h"

UIStatusStripe::UIStatusStripe() : UIStatusStripe([](){return 0;}){
	mSprite.width = mWidth;
	mSprite.height = mHeight;
}

UIStatusStripe::UIStatusStripe(GetValue val) :
		mOverlayColor(Color::White()),
		mScreenPosition(Vec2D::Zero),
		mCropSideLeft(true){
	getValueFunc = val;
}

UIStatusStripe::UIStatusStripe(const UIStatusStripe& other) :
		BMPImage(other),
		mSprite(other.mSprite),
		mOverlayColor(other.mOverlayColor),
		mScreenPosition(other.mScreenPosition),
		mCropSideLeft(other.mCropSideLeft),
		getValueFunc(other.getValueFunc){
}

UIStatusStripe& UIStatusStripe::operator=(const UIStatusStripe& other){
	if(this != &other){
		BMPImage::operator=(other);
	}
	// Use whole image
	this->mSprite.width = other.mWidth;
	this->mSprite.height = other.mHeight;

	this->mOverlayColor = other.mOverlayColor;
	this->mScreenPosition = other.mScreenPosition;
	this->mCropSideLeft = other.mCropSideLeft;
	this->getValueFunc = other.getValueFunc;
	return *this;
}

void UIStatusStripe::SetCoordinates(uint32_t screenX, uint32_t screenY, bool cropFromLeft){
	mScreenPosition = Vec2D(screenX, screenY);
	mCropSideLeft = cropFromLeft;
}

void UIStatusStripe::DrawStripe(Screen& screen){

	int crop{0}, leftCrop{0}, rightCrop{0};

	crop = static_cast<int>(((1.00 - getValueFunc()) * mSprite.width));

	if(mCropSideLeft){
		leftCrop = crop;
	}else{
		rightCrop = crop;
	}
//	Screen& screen, const Vec2D& position, const Sprite& sprite, colorOverlay overlay, bool flipHorizontal, bool globalPosition, int cropLeft, int cropRight
	DrawImagePixels(screen, mScreenPosition, mSprite, [this](const Color& in){ return ModifyColorMultiply(in, mOverlayColor);}, FLIP_HORIZONTAL, GLOBAL_POSITION, leftCrop, rightCrop);
}

