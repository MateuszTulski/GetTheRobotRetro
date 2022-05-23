#include "PursuitScene.h"
#include "MenuScene.h"
#include "Utils.h"
#include "BMPImage.h"
#include "BitmapFont.h"
#include "App.h"
#include "AARectangle.h"

#include <stdint.h>

PursuitScene::PursuitScene() :
		mGameState(GameState::pursuit){
}

void PursuitScene::Init(){
	SetGameControls();
	LoadLevel();
	LoadPlayer();
	LoadRobot();
	SetCamera();
	InitUI();
	InitGameOverPanel();
	mGameState = GameState::pursuit;
}

void PursuitScene::Update(uint32_t deltaTime){
	PhysicsWorld::Singleton().Update(deltaTime);
	if(mGameState == GameState::pursuit){
		mPlayer.Update(deltaTime);
		mRobot.Update(mPursuitController);
		mCamera->Update(mPlayer);
		mPursuitController.Update(mPlayer, mRobot);
		mLevelLoader.Update();
	}
}

void PursuitScene::Draw(Screen& screen){
	mLevelLoader.DrawObjects(screen);
	mPursuitController.DrawUI(screen);
	mRobot.Draw(screen);
	mPlayer.Draw(screen);

	if(mGameState == GameState::gameOverPanel){
		gameOverPanel.DrawPanel(screen);
	}
}

const std::string& PursuitScene::GetSceneName() const{
	const static std::string gameName = {"GetTheRobot Retro!"};
	return gameName;
}

void PursuitScene::SetGameControls(){
	// SPACE -> JUMP OR SELECT BUTTON
	ButtonAction space;
	space.key = GameControlsActions::JumpKey();
	space.action = [this](uint32_t deltaTime, InputState state){
		if(mGameState == GameState::pursuit){
			mPlayer.JumpTrigger(true);
			if(GameControlsActions::IsReleased(state)){
				mPlayer.JumpTrigger(false);
			}
		}
		else if(mGameState == GameState::gameOverPanel){
			gameOverPanel.TriggerActiveButton();
		}
	};
	mGameController.AddInputActionForKey(space);

	// RIGTH ACTION BUTTON
	ButtonAction right;
	right.key = GameControlsActions::RightKey();
	right.action = [this](uint32_t deltaTime, InputState state){

		mPlayer.RunInput(1);
		if(GameControlsActions::IsReleased(state)){
			mPlayer.RunInput(1, true);
		}
	};
	mGameController.AddInputActionForKey(right);

	// LEFT ACTION BUTTON
	ButtonAction left;
	left.key = GameControlsActions::LeftKey();
	left.action = [this](uint32_t deltaTime, InputState state){
		mPlayer.RunInput(-1);
		if(GameControlsActions::IsReleased(state)){
			mPlayer.RunInput(-1, true);
		}
	};
	mGameController.AddInputActionForKey(left);

	// UP ARROW KEY
	ButtonAction upArrow;
	upArrow.key = GameControlsActions::UpKey();
	upArrow.action = [this](uint32_t deltaTime, InputState state){
		if(mGameState == GameState::gameOverPanel){
			gameOverPanel.ChangeActiveButton(true, false);
			if(GameControlsActions::IsReleased(state)){
				gameOverPanel.ChangeActiveButton(true, true);
			}
		}
	};
	mGameController.AddInputActionForKey(upArrow);

	// DOWN ARROW KEY
	ButtonAction downArrow;
	downArrow.key = GameControlsActions::DownKey();
	downArrow.action = [this](uint32_t deltaTime, InputState state){
		if(mGameState == GameState::gameOverPanel){
			gameOverPanel.ChangeActiveButton(false, false);
			if(GameControlsActions::IsReleased(state)){
				gameOverPanel.ChangeActiveButton(false, true);
			}
		}
	};
	mGameController.AddInputActionForKey(downArrow);
}

void PursuitScene::LoadLevel(){
	// LOAD LEVEL
	if(mLevelLoader.LoadGraphics()){
		if(!mLevelLoader.LoadLevelObjects()){
			std::cout << "Error while loading level!" << std::endl;
		}
	}
}

void PursuitScene::LoadPlayer(){
	mPlayer.Init(Vec2D(100, 100));
}

void PursuitScene::LoadRobot(){
	mRobot.Init();
}

void PursuitScene::SetCamera(){
	App::Singleton().SetSceneCamera(Vec2D::Zero, mCamera);
	mCamera->SetFollowOffset(Vec2D(-80, -105));
}

void PursuitScene::InitUI(){
	mPursuitController.InitUI([this](GameState newState){SetGameState(newState);});
}

void PursuitScene::InitGameOverPanel(){
	Size mButtonSize = {130, 30};
	unsigned int mButtonsSpace = 10;
	std::vector<std::string> btnNames = {"Restart", "Exit"};

	float buttonsHeight = (btnNames.size() * mButtonSize.height) + ((btnNames.size()-1) * mButtonsSpace);
	Vec2D buttonsPos(App::Singleton().GetScreenCenter().GetX(), App::Singleton().GetScreenCenter().GetY() - buttonsHeight/2 + mButtonSize.height/2);

	for(auto name : btnNames){
		Button btn;
		btn.InitButton(mButtonSize, name, buttonsPos);
		btn.SetButtonColors(Color(40, 40, 40, 255), Color(37, 240, 217, 120), Color(180, 180, 180, 255), Color::White());
		buttonsPos.SetY(buttonsPos.GetY() + mButtonSize.height + mButtonsSpace);

		if(name == "Restart"){
			Button::ButtonAction acttion = [this](){
				RestartGame();
			};
			btn.SetButtonAction(acttion);
		}
		else if(name == "Exit"){
			Button::ButtonAction acttion = [](){
				std::unique_ptr<MenuScene> menuScene = std::make_unique<MenuScene>();
				App::Singleton().PushScene(std::move(menuScene));
			};
			btn.SetButtonAction(acttion);
		}
		gameOverPanel.AddButton(btn);
	}
}

void PursuitScene::RestartGame(){
	mPlayer.Restart();
	mRobot.Restart();
	mCamera->RestartCamera();
	mPursuitController.Restart();
	mLevelLoader.Restart();

	mGameState = GameState::pursuit;
}







