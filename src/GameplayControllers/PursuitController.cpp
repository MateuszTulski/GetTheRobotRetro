#include "PursuitController.h"
#include "UIStatusStripe.h"
#include "UIDynamicText.h"
#include "App.h"

PursuitController::PursuitController():
		gameTime(0.0f),
		playerRobotDistance(0),
		playerScores(0),
		playerHealth(PLAYER_MAX_HEALTH){
	lastTimeStamp = App::Singleton().GetTime().AppTime();
}

void PursuitController::InitUI(ChangeState changeStateFunc){
	this->changeStateFunc = changeStateFunc;
	LoadStaticGraphics();
	LoadStatusStripes();
	LoadDynamicTexts();
}

void PursuitController::Update(const Player& player, const Robot& robot){
	playerRobotDistance = player.GetPosition().Distance(robot.GetPosition());
	playerHealth = player.GetPlayerHP();
	playerScores = player.GetPlayerScores();

	float timeStamp = App::Singleton().GetTime().AppTime();

	gameTime  += (timeStamp-lastTimeStamp);
	lastTimeStamp = timeStamp;

	if(PlayerFeld(player.GetPosition().GetY()) || RobotEscaped() || playerHealth<=0){
		GameOver(false);
	}
}

void PursuitController::DrawUI(Screen& screen){
	mainUI.DrawPanel(screen);
}

void PursuitController::Restart(){
	gameTime = 0;
}

void PursuitController::RestartGame(){

}

void PursuitController::PauseGame(bool pause){

}

void PursuitController::GameOver(bool success){
	if(success){
		std::cout << "---success---\n";
	}else{
		changeStateFunc(GameState::gameOverPanel);
	}
}

void PursuitController::LoadStaticGraphics(){
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
}

void PursuitController::LoadDynamicTexts(){
	// Dynamic Texts
	UIDynamicText scoreText([this](){ return ScoreDisplayString();});
	scoreText.LoadFont("HemiFont");
	scoreText.SetScreenPosition(140, 10);
	scoreText.SetFontHeight(13);
	scoreText.SetOverlayColor(mUIColor);
	mainUI.AddScoreText(scoreText);

	UIDynamicText timeText([this](){ return TimeDisplayString();});
	timeText.LoadFont("HemiFont");
	timeText.SetScreenPosition(180, 10);
	timeText.SetFontHeight(13);
	timeText.SetOverlayColor(mUIColor);
	mainUI.AddTimeText(timeText);
}

void PursuitController::LoadStatusStripes(){
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

float PursuitController::PlayerLifeNormalizedDecimal(){
	return GetActualLife() / static_cast<float>(PLAYER_MAX_HEALTH);
}

float PursuitController::PlayerDistanceNormalizedDecimal(){
	return GetPlayerRobotDistance() / ROBOT_ESCAPE_DISTANCE;
}

std::string PursuitController::TimeDisplayString(){
	int seconds = GetNumberOfSeconds();
	if(seconds < 10){
		return std::string("0") + std::to_string(seconds);
	}else{
		return std::to_string(seconds);
	}
}

std::string PursuitController::ScoreDisplayString(){
	int scores = GetActualScore();
	if(scores == 0){
		return std::string("00");
	}else if(scores < 10){
		return std::string("0") + std::to_string(scores);
	}else{
		return std::to_string(scores);
	}
	return std::to_string(scores);
}

bool PursuitController::PlayerFeld(const float& yPosition){
	if(yPosition>FALL_DOWN_LEVEL){
		return true;
	}
	return false;
}

bool PursuitController::RobotEscaped(){
	if(playerRobotDistance > ROBOT_ESCAPE_DISTANCE){
		return true;
	}
	return false;
}





