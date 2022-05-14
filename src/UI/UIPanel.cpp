#include "UIPanel.h"
#include "Screen.h"

UIPanel::UIPanel() : isActive(true){

}

void UIPanel::AddStaticImage(const BMPImage& image, const Vec2D& position){
	mImages.emplace(image, position);
}

void UIPanel::AddText(const BitmapFont& font, const Vec2D& position, const GetText& text){

}

void UIPanel::DrawPanel(Screen& screen){
	for(const auto& image : mImages){
//		screen.Draw(image.first, image.second, noManip, false);
//		image.first.DrawImage(screen, image.second, false);
	}
}

void UIPanel::DrawStaticImages(){

}
