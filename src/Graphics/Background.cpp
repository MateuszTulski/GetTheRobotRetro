#include "Background.h"
#include "Camera.h"
#include <stdint.h>

Background::Background() :
		mPosition(Vec2D::Zero),
		repeatHorizontal(true),
		repeatVertical(false){
}

bool Background::InitBackground(const std::string& name){
	if(mImage.LoadImage(name)){
		mPosition.SetY(START_Y_POS);
		return true;
	}
	return false;
}

void Background::Update(const Camera& camera){

	Vec2D cameraOffset = lastCamPosition - camera.GetCameraPosition();
	mPosition -= cameraOffset*0.3f;

	lastCamPosition = camera.GetCameraPosition();
}

void Background::Draw(Screen& screen){
	Vec2D globalTopLeft = screen.GetGlobalPoint(Vec2D::Zero);
	uint32_t rows = screen.GetHeight();
	uint32_t columns = screen.GetWidth();

	for(uint32_t row=0; row < rows; ++row){
		if(globalTopLeft.GetY()-mPosition.GetY()+row < 0){
			continue;
		}
		if(!repeatVertical && globalTopLeft.GetY()-mPosition.GetY()+row>mImage.GetImageHeight()){
			continue;
		}
		for(uint32_t col=0; col < columns; ++col){
			if(!repeatHorizontal && globalTopLeft.GetX()+col>mImage.GetImageWidth()){
				continue;
			}
			Vec2D pixelPos = GetTextureCoordinates(globalTopLeft.GetX()-mPosition.GetX()+col, globalTopLeft.GetY()-mPosition.GetY()+row);
			screen.DrawPixel(col, row, mImage.GetPixelColor(pixelPos.GetX(), pixelPos.GetY()), false);
		}
	}
}

void Background::SetRepeat(bool horizontal, bool vertical){
	repeatHorizontal = horizontal;
	repeatVertical = vertical;
}

Vec2D Background::GetTextureCoordinates(int globalX, int globalY) const{
	int xPos, yPos;

	xPos = globalX % mImage.GetImageWidth();
	yPos = globalY % mImage.GetImageHeight();

	return Vec2D(xPos, yPos);
}
