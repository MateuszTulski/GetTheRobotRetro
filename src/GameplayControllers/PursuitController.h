/*	Responsibilities of this class:
 * - Controll game rules
 * - Controll UI
 * */

#ifndef SRC_GAMEPLAYCONTROLLERS_PURSUITCONTROLLER_H_
#define SRC_GAMEPLAYCONTROLLERS_PURSUITCONTROLLER_H_

#include <string>

#include "UIPanel.h"
#include "Player.h"
#include "Robot.h"

class Screen;

class PursuitController{
public:
	PursuitController();

	void InitUI();

	void Update(const Player& player, const Robot& robot);
	void DrawUI(Screen& screen);

	inline float GetPlayerRobotDistance() const {return playerRobotDistance;}
	inline float GetRobotMaxDistance() const {return ROBOT_ESCAPE_DISTANCE;}

	inline int GetActualScore() const {return playerCoins;}
	inline int GetActualLife() const {return playerHealth;}

	int GetNumberOfSeconds();

	void CollectCoin(const int& points);
	void PlayerDamage(const int& damage);

private:
	const float FALL_DOWN_LEVEL = 400;

	const int PLAYER_MAX_HEALTH = 10;
	const float ROBOT_ESCAPE_DISTANCE = 500.00f;

	float playerRobotDistance;
	int playerCoins;
	int playerHealth = 5;

	float gameStartTime;

	const Color mUIColor = Color(129, 199, 220, 255);
	UIPanel mainUI;

	void RestartGame();
	void PauseGame(bool pause);
	void GameOver(bool success);

	float PlayerLifeNormalizedDecimal();
	float PlayerDistanceNormalizedDecimal();

	std::string TimeDisplayString();
	std::string ScoreDisplayString();

	bool PlayerFeld(const float& yPosition);
	bool RobotEscaped();
};



#endif /* SRC_GAMEPLAYCONTROLLERS_PURSUITCONTROLLER_H_ */
