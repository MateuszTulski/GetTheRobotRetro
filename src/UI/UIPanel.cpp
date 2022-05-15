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

void UIPanel::AddTimeText(const UIDynamicText& text){
	timeText = text;
}

void UIPanel::AddScoreText(const UIDynamicText& text){
	scoreText = text;
}

void UIPanel::DrawPanel(Screen& screen){
	for(const auto& image : mStaticImages){
		image.first.DrawImage(screen, image.second, false, false);
	}
	mPlayerHP.DrawStripe(screen);
	mDistance.DrawStripe(screen);
	timeText.DrawDynamicText(screen);
	scoreText.DrawDynamicText(screen);
}

void UIPanel::DrawStaticImages(){

}
