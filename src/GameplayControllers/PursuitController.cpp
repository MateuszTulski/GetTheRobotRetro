#include "PursuitController.h"

PursuitController::PursuitController():
	playerCoins(0),
	playerHealth(10){

}

void PursuitController::InitUI(){

	SpriteSheet sprites;
	if(sprites.LoadSprite("ui-static")){

		std::vector<std::string> spriteNames = sprites.GetSpritestNames();

		for(auto name : spriteNames){
			BMPImage image;
			image.LoadImageFromSpriteSheet(sprites, name);

			mainUI.AddStaticImage(image, Vec2D(0, 0));
		}
	}
}

void PursuitController::DrawUI(Screen& screen){
	mainUI.DrawPanel(screen);
}

float PursuitController::GetPlayerRobotDistance(){

	return 0;
}

void CollectCoin(){

}

void PlayerDamage(){

}

void RestartGame(){

}

void PauseGame(bool pause){

}
