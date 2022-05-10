#include "Player.h"
#include "Color.h"
#include "Screen.h"
#include "App.h"

#include <cassert>

Player::Player() : mState(PlayerState::idle), mJumpPressed(false), mSpeed(RUN_SPEED_MIN){
	Rigidbody::InitRigidbody(PLAYER_RECT, MASS, true, true);
}

Player::Player(const Player& other) : mState(PlayerState::idle), mJumpPressed(other.mJumpPressed), mSpeed(other.mSpeed){

}

Player::Player(Player&& other) : mState(std::move(other.mState)), mJumpPressed(std::move(other.mJumpPressed)), mSpeed(std::move(other.mSpeed)){

}

void Player::Init(const Vec2D& startPosition){
	// Start position is BOTTOM MIDDLE
	SetPosition(startPosition);
	SetGravityScale(1.5f);
	mLastPosition = startPosition;

	assert(mAnimations.InitAnimations() && "Couldn't init player animations!");

}

void Player::Update(uint32_t deltaTime){

	SetPlayerDirection();
	UpdateSpeed();
	SetRigidbodyVelocity();
	UpdateState();

	mLastPosition = GetPosition();

	mAnimations.Update(mState);
}

void Player::Draw(Screen& screen){

	mAnimations.Draw(screen, mLastPosition, mDirection);

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

void Player::UpdateState(){
	/* TODO
	 * falling detection
	 * grounded detection
	 */
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
