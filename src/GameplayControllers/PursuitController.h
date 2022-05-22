/*	Responsibilities of this class:
 * - Controll game rules
 * - Controll UI
 * */

#ifndef SRC_GAMEPLAYCONTROLLERS_PURSUITCONTROLLER_H_
#define SRC_GAMEPLAYCONTROLLERS_PURSUITCONTROLLER_H_

#include <string>
#include <functional>

#include "UIPanel.h"
#include "Player.h"
#include "Robot.h"

class Screen;

using ChangeState = std::function<void(GameState)>;

class PursuitController{
public:
	PursuitController();

	void InitUI(ChangeState changeStateFunc);

	void Update(const Player& player, const Robot& robot);
	void DrawUI(Screen& screen);

	inline float GetPlayerRobotDistance() const {return playerRobotDistance;}
	inline float GetRobotMaxDistance() const {return ROBOT_ESCAPE_DISTANCE;}

	inline int GetActualScore() const {return playerScores;}
	inline int GetActualLife() const {return playerHealth;}

private:
	float gameTime;
	ChangeState changeStateFunc;

	const float FALL_DOWN_LEVEL = 400;

	const int PLAYER_MAX_HEALTH = 10;
	const float ROBOT_ESCAPE_DISTANCE = 1000.00f;

	float playerRobotDistance;
	int playerScores;
	int playerHealth;

	float lastTimeStamp;

	const Color mUIColor = Color(129, 199, 220, 255);
	UIPanel mainUI;

	void RestartGame();
	void PauseGame(bool pause);
	void GameOver(bool success);

	inline int GetNumberOfSeconds() {return static_cast<int>(gameTime);}

	float PlayerLifeNormalizedDecimal();
	float PlayerDistanceNormalizedDecimal();

	std::string TimeDisplayString();
	std::string ScoreDisplayString();

	bool PlayerFeld(const float& yPosition);
	bool RobotEscaped();
};



#endif /* SRC_GAMEPLAYCONTROLLERS_PURSUITCONTROLLER_H_ */
