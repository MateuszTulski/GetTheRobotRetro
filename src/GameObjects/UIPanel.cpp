#include "UIPanel.h"
#include "Screen.h"

UIPanel::UIPanel() : isActive(true), noManip(ColorManipulation::NoColorManipulation()){

}

void UIPanel::AddStaticImage(const BMPImage& image, const Vec2D& position){
	mImages.emplace(image, Vec2D(1, 1));
}

void UIPanel::AddText(const BitmapFont& font, const Vec2D& position, const GetText& text){

}

void UIPanel::DrawPanel(Screen& screen){
	for(const auto& image : mImages){
		screen.Draw(image.first, image.second, noManip, false);
	}
}

void UIPanel::DrawStaticImages(){

}
