#ifndef SRC_GAMEOBJECTS_PLAYER_H_
#define SRC_GAMEOBJECTS_PLAYER_H_

#include "AARectangle.h"
#include "Rigidbody.h"
#include "Animation.h"

class Screen;
class BoundaryEdge;

class Player : public Rigidbody {
public:
	Player();

	Player(const Player& other);
	Player(Player&& other);

	void Init(const Vec2D& startPosition);
	void Update(uint32_t deltaTime);
	void Draw(Screen& screen);
	void MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& point, bool limitToEdge);

	void Run(signed int direction, bool released = false);
	void Jump(bool jumpPressed);

	void SetPosition(Vec2D bottomMiddlePoint);
	Vec2D GetPosition() const;

private:
	bool mJumpPressed;
	bool isRunning;

	Animation mAnimation;
	float mSpeed;
	Vec2D mLastPosition;

	float resetSpeedTimer;
	float resetSpeedDelay = 0.7f;

	const float RUN_SPEED_MIN = 30.0f;
	const float RUN_SPEED_MAX = 160.0f;
	const float ACCELERATION = 4.0f;

	const float MASS = 65.0f;
	const float WIDTH = 12;
	const float HEIGHT = 30;
	const float JUMP_FORCE = 28000;

	bool RIGHT_KEY_PRESSED = false;
	bool LEFT_KEY_PRESSED = false;

	const AARectangle PLAYER_RECT = {Vec2D::Zero, WIDTH, HEIGHT};

	void UpdateSpeed();
	void SetRigidbodyVelocity();

	void ResetSpeedWhenNotMoving();
};



#endif /* SRC_GAMEOBJECTS_PLAYER_H_ */
