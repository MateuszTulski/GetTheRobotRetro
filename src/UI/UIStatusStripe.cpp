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

	std::cout << "new copy: " << "new assignment" << std::endl;
	return *this;
}

void UIStatusStripe::SetCoordinates(uint32_t screenX, uint32_t screenY, bool cropFromLeft){
	mScreenPosition = Vec2D(screenX, screenY);
	mCropSideLeft = cropFromLeft;
}

void UIStatusStripe::DrawStripe(Screen& screen){

	int crop{0}, leftCrop{0}, rightCrop{0};

	crop = static_cast<int>((getValueFunc() * mSprite.width) / 100);

	if(mCropSideLeft){
		leftCrop = crop;
	}else{
		rightCrop = crop;
	}

	DrawImagePixels(screen, Vec2D(0,0), mSprite, [this](const Color& in){ return ModifyColorMultiply(in, mOverlayColor);}, FLIP_HORIZONTAL, GLOBAL_POSITION, leftCrop, rightCrop);
}
