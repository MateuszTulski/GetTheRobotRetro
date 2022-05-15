#include "UIPanel.h"
#include "Screen.h"

UIPanel::UIPanel() : isActive(true){

}

void UIPanel::AddStaticImage(const BMPImage& image, const Vec2D& position){
	mStaticImages.emplace(image, position);
}

void UIPanel::AddHPStripe(const UIStatusStripe& stripe){
	mPlayerHP = stripe;
}

void UIPanel::AddDistanceStripe(const UIStatusStripe& stripe){
	mDistance = stripe;
}

void UIPanel::DrawPanel(Screen& screen){
	for(const auto& image : mStaticImages){
		image.first.DrawImage(screen, image.second, false, false);
	}
	mPlayerHP.DrawStripe(screen);
	mDistance.DrawStripe(screen);
}

void UIPanel::DrawStaticImages(){

}
