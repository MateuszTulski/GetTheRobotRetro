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

	/// FLOOR ---- TEMP -----
	AARectangle floorRec(Vec2D(0, 400), 1000, 40);
	floor.Init(floorRec, 0, false, true);

	if(platformSpriteTemp.LoadSprite("platform"))
	{
		std::string name("platform-left");
		platformSpriteTemp.GetSprite(name);

//		platformSprite = std::make_shared<SpriteSheet>();
//		Platform plat(Line2D(Vec2D(10, 10), Vec2D(300, 10)), platformSprite);
	}


	// LOAD LEVEL
	if(mLevelLoader.LoadGraphics()){
		if(mLevelLoader.LoadPlatforms()){

		}
	}

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

	// Draw Level
	mLevelLoader.DrawObjects(screen);

}

const std::string& PursuitScene::GetSceneName() const
{
	const static std::string gameName = {"GetTheRobot Retro!"};
	return gameName;
}

