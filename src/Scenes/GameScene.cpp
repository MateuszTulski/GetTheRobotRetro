#include "GameScene.h"
#include "PhysicsWorld.h"
#include "Rigidbody.h"
#include "App.h"

GameScene::GameScene(){
}

void GameScene::Init(){
	// Set player start position
	mPlayer.Init(Vec2D(App::Singleton().GetWidht()/2, App::Singleton().GetHeight()/2));

	AARectangle floorRec(Vec2D(0, App::Singleton().GetHeight()-20), Vec2D(App::Singleton().GetWidht(), App::Singleton().GetHeight()));
	floor.Init(floorRec, 0, false, true);


}

void GameScene::Update(uint32_t deltaTime){
	PhysicsWorld::Singleton().Update(deltaTime);
	mPlayer.Update(deltaTime);
}

void GameScene::Draw(Screen& screen){
	mPlayer.Draw(screen);
	floor.Draw(screen);
}

const std::string& GameScene::GetSceneName() const{
	const static std::string gameName = {"GetTheRobot Retro!"};
	return gameName;
}

