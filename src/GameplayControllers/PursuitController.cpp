#include "PursuitController.h"
#include "UIStatusStripe.h"

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
			Sprite sprite = sprites.GetSpriteCoordinates(name);

			image.LoadImageFromSpriteSheet(sprites, name);

			if(sprite.flipX){
				image.FlipImageHorizontal();
			}

			mainUI.AddStaticImage(image, Vec2D(sprite.screenX, sprite.screenY));
		}
	}

	// Player HP and Distance stripes
	SpriteSheet statusStripes;
	if(statusStripes.LoadSprite("ui-stripes")){
		Sprite sprite = statusStripes.GetSpriteCoordinates("life_stripe");

		UIStatusStripe hpStripe([this](){return GetActualLife() / static_cast<float>(PLAYER_MAX_HEALTH);});
		hpStripe.LoadImageFromSpriteSheet(statusStripes, "life_stripe");
		hpStripe.SetCoordinates(sprite.screenX, sprite.screenY, false);

		mainUI.AddHPStripe(hpStripe);
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
