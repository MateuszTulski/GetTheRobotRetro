#include "PursuitController.h"
#include "UIStatusStripe.h"

PursuitController::PursuitController():
	playerCoins(0),
	playerHealth(PLAYER_MAX_HEALTH){
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
		Sprite hpSprite = statusStripes.GetSpriteCoordinates("life_stripe");
		UIStatusStripe hpBar([this](){return PlayerLifeNormalizedDecimal();});
		hpBar.LoadImageFromSpriteSheet(statusStripes, "life_stripe");
		hpBar.SetCoordinates(hpSprite.screenX, hpSprite.screenY, false);
		mainUI.AddHPStripe(hpBar);

		Sprite distanceSprite = statusStripes.GetSpriteCoordinates("distance_stripe");
		UIStatusStripe distanceBar([this](){return PlayerDistanceNormalizedDecimal();});
		distanceBar.LoadImageFromSpriteSheet(statusStripes, "distance_stripe");
		distanceBar.FlipImageHorizontal();
		distanceBar.SetCoordinates(distanceSprite.screenX, distanceSprite.screenY, true);
		mainUI.AddDistanceStripe(distanceBar);
	}
}

void PursuitController::DrawUI(Screen& screen){
	mainUI.DrawPanel(screen);
}

float PursuitController::GetPlayerRobotDistance(){

	return 0;
}

void PursuitController::CollectCoin(){

}

void PursuitController::PlayerDamage(){

}

void PursuitController::RestartGame(){

}

void PursuitController::PauseGame(bool pause){

}

float PursuitController::PlayerLifeNormalizedDecimal(){
	return GetActualLife() / static_cast<float>(PLAYER_MAX_HEALTH);
}

float PursuitController::PlayerDistanceNormalizedDecimal(){
	return GetPlayerRobotDistance() / ROBOT_ESCAPE_DISTANCE;
}






