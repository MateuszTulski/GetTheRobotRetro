#include "GameScene.h"

GameScene::GameScene(std::unique_ptr<Game> optrGame) : mGame(std::move(optrGame)){

}

void GameScene::Init(){
	mGame->Init(mGameController);
}

void GameScene::Update(uint32_t deltaTime){
	mGame->Update(deltaTime);
}

void GameScene::Draw(Screen& screen){
	mGame->Draw(screen);
}

const std::string& GameScene::GetSceneName() const{
	return mGame->GetSceneName();
}

