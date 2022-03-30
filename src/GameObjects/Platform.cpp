#include "Platform.h"
#include "App.h"
#include "ColorManipulation.h"
#include "Rigidbody.h"
#include "AARectangle.h"
#include "BMPImage.h"

Platform::Platform() : Platform(Line2D(Vec2D::Zero, Vec2D::Zero), nullptr){
}

Platform::Platform(const Line2D& line, std::shared_ptr<SpriteSheet> sprite) : mLine(line), mnoptrSprite(sprite){

	ColorManipulation manip;
	mColorManipulator = manip;

	if(tempPlatforms.LoadSprite("HemiFont")){

	}

	if(tempImage.LoadImage(App::Singleton().GetBasePath() + "Assets/rocket.bmp")){

	}
}

Platform::~Platform(){
}

void Platform::Draw(Screen& screen)
{
//	screen.Draw(mAARect, Color().Green());

	screen.Draw(*mnoptrSprite, "platform-left", mAARect.GetTopLeft(), mColorManipulator);
}
void Platform::Update(uint32_t deltaTime)
{

}
