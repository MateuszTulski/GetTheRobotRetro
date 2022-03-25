#include "MenuScene.h"
#include "Screen.h"
#include "AARectangle.h"
#include "App.h"

MenuScene::MenuScene(){}
void MenuScene::Init()
{
	std::vector<std::string> btnNames = {"Start", "Options", "Scores", "Exit"};

	float buttonsHeight = (btnNames.size() * mButtonSize.height) + ((btnNames.size()-1) * mButtonsSpace);

	Vec2D buttonsPos(App::Singleton().GetScreenCenter().GetX(), App::Singleton().GetScreenCenter().GetY() - buttonsHeight/2 + mButtonSize.height/2);


	for(auto name : btnNames)
	{
		Button btn;
		btn.InitButton(mButtonSize, name, buttonsPos);

		buttonsPos.SetY(buttonsPos.GetY() + mButtonSize.height + mButtonsSpace);

		mButtons.push_back(btn);
	}
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
