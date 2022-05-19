#include "PursuitScene.h"
#include "Utils.h"
#include "BMPImage.h"
#include "BitmapFont.h"
#include "App.h"
#include "AARectangle.h"

#include <stdint.h>

PursuitScene::PursuitScene(){
}

void PursuitScene::Init(){
	SetGameControls();
	LoadLevel();
	LoadPlayer();
	LoadRobot();
	SetCamera();
	InitUI();
}

void PursuitScene::Update(uint32_t deltaTime){
	PhysicsWorld::Singleton().Update(deltaTime);
	mPlayer.Update(deltaTime);
	mRobot.Update();
	mCamera->Update(mPlayer);
	mPursuitController.Update(mPlayer, mRobot);
}

void PursuitScene::Draw(Screen& screen){
	mPlayer.Draw(screen);
	mRobot.Draw(screen);
	mLevelLoader.DrawObjects(screen);
	mPursuitController.DrawUI(screen);
}

const std::string& PursuitScene::GetSceneName() const{
	const static std::string gameName = {"GetTheRobot Retro!"};
	return gameName;
}

void PursuitScene::SetGameControls(){
	// Set GameController
	ButtonAction jump;
	jump.key = GameControlsActions::JumpKey();
	jump.action = [this](uint32_t deltaTime, InputState state){

		mPlayer.JumpTrigger(true);

		if(GameControlsActions::IsReleased(state)){
			mPlayer.JumpTrigger(false);
		}
	};
	mGameController.AddInputActionForKey(jump);

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
	mRobot.Init(Vec2D(100, 150));
}

void PursuitScene::SetCamera(){
	App::Singleton().SetSceneCamera(Vec2D::Zero, mCamera);
	mCamera->SetFollowOffset(Vec2D(-80, -105));
}

void PursuitScene::InitUI(){
	mPursuitController.InitUI();
}
