#include "MenuScene.h"
#include "PursuitScene.h"
#include "Screen.h"
#include "AARectangle.h"
#include "App.h"

MenuScene::MenuScene() : mActiveButton(0){
}
void MenuScene::Init()
{
	// SET BUTTONS

	std::vector<std::string> btnNames = {"Start", "Options", "Scores", "Exit"};

	float buttonsHeight = (btnNames.size() * mButtonSize.height) + ((btnNames.size()-1) * mButtonsSpace);

	Vec2D buttonsPos(App::Singleton().GetScreenCenter().GetX(), App::Singleton().GetScreenCenter().GetY() - buttonsHeight/2 + mButtonSize.height/2);


	for(auto name : btnNames){
		Button btn;
		btn.InitButton(mButtonSize, name, buttonsPos);
		btn.SetButtonColors(Color(40, 40, 40, 255), Color(37, 240, 217, 120), Color(180, 180, 180, 255), Color::White());
		buttonsPos.SetY(buttonsPos.GetY() + mButtonSize.height + mButtonsSpace);
		mButtons.push_back(btn);
	}

	ResetButtons();

	// SET ACTIONS FOR BUTTONS
	for(auto& btn : mButtons)
	{
		std::string name = btn.GetButtonName();
		if(name == "Start")
		{
			Button::ButtonAction acttion = [](){
					std::unique_ptr<PursuitScene> pursuitScene = std::make_unique<PursuitScene>();
					App::Singleton().PushScene(std::move(pursuitScene));
			};
			btn.SetButtonAction(acttion);
		}
	}

	// SCENE NAVIGATION
	ButtonAction upArrow;
	upArrow.key = GameControlsActions::UpKey();
	upArrow.action = [this](uint32_t deltaTime, InputState state){
		if(GameControlsActions::IsPressed(state)){
			PrevButton();
		}
	};
	mGameController.AddInputActionForKey(upArrow);

	ButtonAction downArrow;
	downArrow.key = GameControlsActions::DownKey();
	downArrow.action = [this](uint32_t deltaTime, InputState state){
		if(GameControlsActions::IsPressed(state)){
			NextButton();
		}
	};
	mGameController.AddInputActionForKey(downArrow);

	ButtonAction executeButton;
	executeButton.key = GameControlsActions::JumpKey();
	executeButton.action = [this](uint32_t detlatime, InputState state){
		if(GameControlsActions::IsPressed(state)){
			for(auto& btn : mButtons){
				if(btn.IsActive())
					btn.ExecuteAction();
			}
		}
	};
	mGameController.AddInputActionForKey(executeButton);

}
void MenuScene::Update(uint32_t dt)
{

}
void MenuScene::Draw(Screen& theScreen)
{
	for(auto& b : mButtons)
	{
		b.Draw(theScreen);
	}
}
const std::string& MenuScene::GetSceneName() const
{
	static const std::string name("Main menu");
	return name;
}

void MenuScene::NextButton()
{
	mActiveButton ++;
	if(mActiveButton > mButtons.size()-1){
		mActiveButton = 0;
	}
	ResetButtons();
}

void MenuScene::PrevButton()
{
	if(mActiveButton == 0){
		mActiveButton = mButtons.size();
	}
	mActiveButton--;
	ResetButtons();
}

void MenuScene::ResetButtons()
{
	for(size_t i = 0; i < mButtons.size(); i++)
	{
		if(i == mActiveButton){
			mButtons[i].SetButtonActive(true);
		}else{
			mButtons[i].SetButtonActive(false);
		}
	}
}

