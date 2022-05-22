#ifndef SRC_GAMEOBJECTS_PLAYER_H_
#define SRC_GAMEOBJECTS_PLAYER_H_

#include "Enums.h"
#include "AARectangle.h"
#include "Rigidbody.h"
#include "PlayerAnimations.h"
#include "Circle.h"

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

	void Restart();

	void RunInput(signed int direction, bool released = false);
	void JumpTrigger(bool jumpPressed);

	void SetPosition(Vec2D bottomMiddlePoint);
	Vec2D GetPosition() const;

	inline PlayerState GetState() const {return mState;}

	inline int GetPlayerHP() const {return mHP;}
	inline int GetPlayerScores() const {return mScores;}

	void HitThePlayer(int damage);
	void FreezeThePlayer(bool freeze);

	void OnCollision(Rigidbody& outCollider) override;

private:
	PlayerState mState;
	PlayerAnimations mAnimations;

	bool mJumpPressed;

	bool firstJumpUsed = false;
	bool secondJumpUsed = false;

	float mSpeed;
	Vec2D mStartPosition;
	Vec2D mLastPosition;
	int mDirection = 1;

	int mHP = 10;
	int mScores = 0;

	float resetSpeedTimer = 0.0f;
	float resetSpeedDelay = 0.7f;

	const float RUN_SPEED_MIN = 30.0f;
	const float RUN_SPEED_MAX = 120.0f;
	const float ACCELERATION = 3.0f;

	const float MASS = 65.0f;
	const float WIDTH = 12;
	const float HEIGHT = 30;
	const float JUMP_FORCE = 28000;

	bool RIGHT_KEY_PRESSED = false;
	bool LEFT_KEY_PRESSED = false;

	const AARectangle PLAYER_RECT = {Vec2D::Zero, WIDTH, HEIGHT};

	void UpdateSpeed();
	void UpdatePlayerState();
	void SetRigidbodyVelocity();
	void ResetSpeedWhenNotMoving();
	void SetPlayerDirection();
	void JumpSequence();

	bool IsGrounded();
	bool CanJumpFirst();
	bool CanJumpSecond();
	void ResetUsedJumps();
};



#endif /* SRC_GAMEOBJECTS_PLAYER_H_ */
