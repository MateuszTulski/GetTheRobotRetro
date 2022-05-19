#include "Platform.h"
#include "App.h"
#include "ColorManipulation.h"
#include "Rigidbody.h"
#include "AARectangle.h"
#include "BMPImage.h"
#include "LevelLoader.h"

Platform::Platform() : Platform(Line2D(Vec2D::Zero, Vec2D::Zero), nullptr){
}

Platform::Platform(const Line2D& line, std::shared_ptr<SpriteSheet> sprite) : mLine(line), mSegments(0), mnoptrSprite(sprite){

	mSegments = static_cast<int>(line.GetP1().GetX()) - static_cast<int>(line.GetP0().GetX()) + 2;
}


Platform::Platform(const Platform& other) : mLine(std::move(other.mLine)), mSegments(std::move(other.mSegments)), mnoptrSprite(std::move(other.mnoptrSprite)){

}

Platform::~Platform(){

}

void Platform::Draw(Screen& screen){
	if(mSegments >= 3){
		// Draw left side
		mnoptrSprite->DrawSprite(screen, mAARect.GetTopLeft(), "left");
		// Draw middle segments
		for(unsigned int i = 2; i < mSegments-1; i++){
			mnoptrSprite->DrawSprite(screen, mAARect.GetTopLeft()+Vec2D(((i-1)*LevelLoader::LEVEL_GRID_SIZE), 0), "middle");
		}
		// Draw right side
		mnoptrSprite->DrawSprite(screen, mAARect.GetTopLeft()+Vec2D(((mSegments-2)*LevelLoader::LEVEL_GRID_SIZE), 0), "right");

	}else if(mSegments == 2){

	}
}
