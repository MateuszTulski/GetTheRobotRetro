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
	// Set GameController
	ButtonAction jump;
	jump.key = GameControlsActions::JumpKey();
	jump.action = [this](uint32_t deltaTime, InputState state){

		mPlayer.JumpTrigger(true);

		if(GameControlsActions::IsReleased(state)){ // @suppress("Ambiguous problem")
			mPlayer.JumpTrigger(false);
		}
	};
	mGameController.AddInputActionForKey(jump);

	// RIGTH ACTION BUTTON
	ButtonAction right;
	right.key = GameControlsActions::RightKey();
	right.action = [this](uint32_t deltaTime, InputState state){

		mPlayer.RunInput(1);

		if(GameControlsActions::IsReleased(state)){ // @suppress("Ambiguous problem")
			mPlayer.RunInput(1, true);
		}
	};
	mGameController.AddInputActionForKey(right);

	// LEFT ACTION BUTTON
	ButtonAction left;
	left.key = GameControlsActions::LeftKey();
	left.action = [this](uint32_t deltaTime, InputState state){

		mPlayer.RunInput(-1);

		if(GameControlsActions::IsReleased(state)){ // @suppress("Ambiguous problem")
			mPlayer.RunInput(-1, true);
		}
	};
	mGameController.AddInputActionForKey(left);

	// Set player start position
	mPlayer.Init(Vec2D(100, 100));

	// LOAD LEVEL
	if(mLevelLoader.LoadGraphics()){
		if(!mLevelLoader.LoadPlatforms()){
			std::cout << "Error while loading level!" << std::endl;
		}
	}

	App::Singleton().SetSceneCamera(Vec2D::Zero, mCamera);
	mCamera->SetFollowOffset(Vec2D(-80, -105));

	mPursuitController.InitUI();

	tempImage.LoadImage(App::Singleton().GetBasePath() + "Assets/rocket.bmp");
	tempImage.ScaleImage(0.5, 0.5, false);
}

void PursuitScene::Update(uint32_t deltaTime){
	PhysicsWorld::Singleton().Update(deltaTime);
	mPlayer.Update(deltaTime);
	mCamera->Update(mPlayer);
}

void PursuitScene::Draw(Screen& screen){
	tempImage.DrawImage(screen, Vec2D(10,10), true);

	mPlayer.Draw(screen);
	mLevelLoader.DrawObjects(screen);
	mPursuitController.DrawUI(screen);
}

const std::string& PursuitScene::GetSceneName() const{
	const static std::string gameName = {"GetTheRobot Retro!"};
	return gameName;
}

