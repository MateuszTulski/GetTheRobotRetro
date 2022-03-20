#include "GameScene.h"

GameScene::GameScene(){
}

void GameScene::Init(){

}

void GameScene::Update(uint32_t deltaTime){

}

void GameScene::Draw(Screen& screen){

}

const std::string& GameScene::GetSceneName() const{
	const static std::string gameName = {"GetTheRobot Retro!"};
	return gameName;
}

