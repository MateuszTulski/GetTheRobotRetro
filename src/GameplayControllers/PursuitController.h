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

	int playerCoins;
	int playerHealth;

	UIPanel mainUI;

	void RestartGame();
	void PauseGame(bool pause);

};



#endif /* SRC_GAMEPLAYCONTROLLERS_PURSUITCONTROLLER_H_ */
