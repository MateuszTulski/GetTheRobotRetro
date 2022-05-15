#ifndef SRC_GAMEPLAYCONTROLLERS_PURSUITCONTROLLER_H_
#define SRC_GAMEPLAYCONTROLLERS_PURSUITCONTROLLER_H_

#include "UIPanel.h"

class Screen;

class PursuitController{
public:
	PursuitController();

	void InitUI();

	void DrawUI(Screen& screen);

	float GetPlayerRobotDistance();
	int GetActualScore();
	inline int GetActualLife() {return playerHealth;}
	int GetNumberOfSeconds();

	void CollectCoin();
	void PlayerDamage();

private:
	const float FALL_DOWN_LEVEL = 400;

	const int PLAYER_MAX_HEALTH = 10;
	const float ROBOT_ESCAPE_DISTANCE = 500.00f;

	int playerCoins;
	int playerHealth = 5;

	UIPanel mainUI;

	void RestartGame();
	void PauseGame(bool pause);

	float PlayerLifeNormalizedDecimal();
	float PlayerDistanceNormalizedDecimal();
};



#endif /* SRC_GAMEPLAYCONTROLLERS_PURSUITCONTROLLER_H_ */
