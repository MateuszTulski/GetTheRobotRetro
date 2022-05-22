#include "UIPanel.h"
#include "Screen.h"

UIPanel::UIPanel() :
		isActive(true),
		changeBtnReleased(true){
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

void UIPanel::AddRectangleFrame(const AARectangle& frame, const Color& color){
	mUIFrames.push_back(std::pair<AARectangle, Color>(frame, color));
}

void UIPanel::AddButton(const Button& button){
	mButtons.push_back(button);
	mButtons.at(0).SetButtonActive(true);
}

void UIPanel::TriggerActiveButton(){
	for(Button& btn : mButtons){
		if(btn.IsActive()){
			btn.ExecuteAction();
			return;
		}
	}
}

void UIPanel::ChangeActiveButton(bool moveUp, bool changeBtnReleased){
	if(!this->changeBtnReleased){
		this->changeBtnReleased = changeBtnReleased;
		return;
	}

	int activeBtn{0};
	for(Button& btn : mButtons){
		if(btn.IsActive()){
			btn.SetButtonActive(false);
			break;
		}
		activeBtn++;
	}

	moveUp ? ++activeBtn : --activeBtn;

	if(activeBtn < 0){
		activeBtn = mButtons.size() - 1;
	}

	if(static_cast<size_t>(activeBtn) >= mButtons.size()){
		activeBtn = 0;
	}

	mButtons.at(activeBtn).SetButtonActive(true);
}

void UIPanel::DrawPanel(Screen& screen){
	for(const auto& image : mStaticImages){
		image.first.DrawImage(screen, image.second, false, false);
	}
	for(const auto& f : mUIFrames){
		screen.Draw(f.first, f.second, false, Color::White(), false);
	}
	for(Button& btn : mButtons){
		btn.Draw(screen);
	}

	mPlayerHP.DrawStripe(screen);
	mDistance.DrawStripe(screen);

	if(timeText.IsActive()){
		timeText.DrawDynamicText(screen);
	}
	if(scoreText.IsActive()){
		scoreText.DrawDynamicText(screen);
	}
}

void UIPanel::DrawStaticImages(){

}
