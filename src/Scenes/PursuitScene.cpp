#include "PursuitScene.h"
#include "Utils.h"
#include "BMPImage.h"
#include "BitmapFont.h"
#include "App.h"
#include <stdint.h>

PursuitScene::PursuitScene(){
}

void PursuitScene::Init(){
	// Set GameController
	ButtonAction jump;
	jump.key = GameController::JumpKey();
	jump.action = [this](uint32_t deltaTime, InputState state){

		mPlayer.Jump(true);

		if(GameController::IsReleased(state)){ // @suppress("Ambiguous problem")
			mPlayer.Jump(false);
		}
	};
	mGameController.AddInputActionForKey(jump);

	// RIGTH ACTION BUTTON
	ButtonAction right;
	right.key = GameController::RightKey();
	right.action = [this](uint32_t deltaTime, InputState state){

		mPlayer.Run(1);

		if(GameController::IsReleased(state)){ // @suppress("Ambiguous problem")
			mPlayer.Run(1, true);
		}
	};
	mGameController.AddInputActionForKey(right);

	// LEFT ACTION BUTTON
	ButtonAction left;
	left.key = GameController::LeftKey();
	left.action = [this](uint32_t deltaTime, InputState state){

		mPlayer.Run(-1);

		if(GameController::IsReleased(state)){ // @suppress("Ambiguous problem")
			mPlayer.Run(-1, true);
		}
	};
	mGameController.AddInputActionForKey(left);

	// Set player start position
	mPlayer.Init(Vec2D(App::Singleton().GetWidht()/2, App::Singleton().GetHeight()/2));

	// Init the floor (temporary)
	AARectangle floorRec(Vec2D(0, App::Singleton().GetHeight()-20), Vec2D(App::Singleton().GetWidht(), App::Singleton().GetHeight()));
	floor.Init(floorRec, 0, false, true);

	//////// ---- TEMP --------- ///////////
	Size buttonSize;
	buttonSize.width = 230;
	buttonSize.height = 60;
	mTempButton.InitButton(buttonSize, "play", Vec2D(App::Singleton().GetWidht()/2, App::Singleton().GetHeight()/2));

}

void PursuitScene::Update(uint32_t deltaTime)
{
	PhysicsWorld::Singleton().Update(deltaTime);
	mPlayer.Update(deltaTime);
}

void PursuitScene::Draw(Screen& screen)
{
	mPlayer.Draw(screen);
	floor.Draw(screen);
	mTempButton.Draw(screen);

}

const std::string& PursuitScene::GetSceneName() const
{
	const static std::string gameName = {"GetTheRobot Retro!"};
	return gameName;
}

