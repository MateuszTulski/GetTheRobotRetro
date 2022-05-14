#include "UIPanel.h"
#include "Screen.h"

UIPanel::UIPanel() : isActive(true){

}

void UIPanel::AddStaticImage(const BMPImage& image, const Vec2D& position){
	mStaticImages.emplace(image, position);
}

void UIPanel::AddHPStripe(const UIStatusStripe& stripe){
	std::cout << "stripe: " << stripe.GetImageWidth() << std::endl;
	mPlayerHP = stripe;
	std::cout << "player: " << mPlayerHP.GetImageWidth() << std::endl;
}

void UIPanel::DrawPanel(Screen& screen){
	for(const auto& image : mStaticImages){
		image.first.DrawImage(screen, image.second, false, false);
	}
	mPlayerHP.DrawStripe(screen);
}

void UIPanel::DrawStaticImages(){

}
