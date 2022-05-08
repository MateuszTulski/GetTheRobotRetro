#include "Player.h"
#include "Color.h"
#include "Screen.h"
#include "App.h"

Player::Player() : mJumpPressed(false), isRunning(false), mSpeed(RUN_SPEED_MIN){
	Rigidbody::InitRigidbody(PLAYER_RECT, MASS, true, true);
	mAnimation.SetFrameRate(5);
}

Player::Player(const Player& other) : mJumpPressed(other.mJumpPressed), isRunning(other.isRunning), mSpeed(other.mSpeed){

}

Player::Player(Player&& other) : mJumpPressed(std::move(other.mJumpPressed)), isRunning(std::move(other.isRunning)), mSpeed(std::move(other.mSpeed)){

}

void Player::Init(const Vec2D& startPosition){
	// Start position is BOTTOM MIDDLE
	SetPosition(startPosition);
	SetGravityScale(1.5f);
	mLastPosition = startPosition;

	// Load player Animations
//	mAnimation.LoadSprite("player-run");
//	mAnimation.ScaleAnimationSprite(0.9, 0.9);
//	mAnimation.SetVerticalAlign(AnimVerticalAlign::Bottom);

	Animation run(3);
	run.LoadSprite("player-run");
	run.ScaleAnimationSprite(0.9, 0.9);
	run.SetVerticalAlign(AnimVerticalAlign::Bottom);

	Animation idle(10);
	idle.LoadSprite("player-idle");
	idle.ScaleAnimationSprite(0.9, 0.9);
	idle.SetVerticalAlign(AnimVerticalAlign::Bottom);

	mAnimator.AddAnimation("run", run);
	mAnimator.AddAnimation("idle", idle);
	mAnimator.SetActiveAnimation("idle");
}

void Player::Update(uint32_t deltaTime){

	mAnimator.Update();

	SetPlayerDirection();
	UpdateSpeed();
	SetRigidbodyVelocity();

	mLastPosition = GetPosition();
}

void Player::Draw(Screen& screen){

	if(mDirection > 0){
//		mAnimation.Draw(screen, GetPosition());
		mAnimator.DrawActiveAnimation(screen, GetPosition());
	}else{
//		mAnimation.DrawFlipped(screen, GetPosition(), true, false);
		mAnimator.DrawFlippedActiveAnimation(screen, GetPosition(), true, false);
	}
}

void Player::MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& point, bool limitToEdge){

}

void Player::RunInput(signed int direction, bool released){

	if(direction > 0){
		if(!RIGHT_KEY_PRESSED && !released){
			RIGHT_KEY_PRESSED = true;
		}else if(released){
			RIGHT_KEY_PRESSED = false;
		}
	}
	else
	{
		if(!LEFT_KEY_PRESSED && !released){
			LEFT_KEY_PRESSED = true;
		}else if(released){
			LEFT_KEY_PRESSED = false;
		}
	}
}

void Player::Jump(bool jumpPressed)
{
	if(jumpPressed && !mJumpPressed)
	{
		mJumpPressed = true;
		AddForce(Vec2D(0, -JUMP_FORCE));
	}
	else if(!jumpPressed)
	{
		// False means jump button have been released
		mJumpPressed = false;
	}
}

void Player::SetPosition(Vec2D bottomMiddlePoint){
	Vec2D newPos = bottomMiddlePoint - Vec2D(HEIGHT, WIDTH/2);
	mAARect.MoveTo(newPos);
}

Vec2D Player::GetPosition() const{

	return Vec2D(mAARect.GetBottomRight().GetX() - WIDTH/2, mAARect.GetBottomRight().GetY());
}

void Player::UpdateSpeed(){

	ResetSpeedWhenNotMoving();

	if(mLastPosition != GetPosition() && mSpeed < RUN_SPEED_MAX)
	{
		float newSpeed = mSpeed + ACCELERATION;
		if(newSpeed > RUN_SPEED_MAX)
		{
			newSpeed = RUN_SPEED_MAX;
		}

		mSpeed = newSpeed;
	}
}

void Player::ResetSpeedWhenNotMoving(){

	if(GetPosition() == mLastPosition)
	{
		resetSpeedTimer += App::Singleton().GetTime().DeltaTime();

		if(resetSpeedTimer > resetSpeedDelay && mSpeed != RUN_SPEED_MIN)
		{
			mSpeed = RUN_SPEED_MIN;
			resetSpeedTimer = 0;
		}
	}
}

void Player::SetRigidbodyVelocity(){

	if(RIGHT_KEY_PRESSED && !LEFT_KEY_PRESSED)
	{
		SetHorizontalVelocity(mSpeed);
	}
	else if(LEFT_KEY_PRESSED && !RIGHT_KEY_PRESSED)
	{
		SetHorizontalVelocity(-mSpeed);
	}
	else
	{
		SetHorizontalVelocity(0);
	}
}

void Player::SetPlayerDirection(){

	if(RIGHT_KEY_PRESSED && !LEFT_KEY_PRESSED && mDirection < 0 && mLastPosition != GetPosition()){
		mDirection = 1;
	}
	if(LEFT_KEY_PRESSED && !RIGHT_KEY_PRESSED && mDirection > 0 && mLastPosition != GetPosition()){
		mDirection = -1;
	}
}
