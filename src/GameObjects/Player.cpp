#include "Player.h"
#include "Color.h"
#include "Screen.h"
#include "App.h"

Player::Player() : mJumpPressed(false), isRunning(false), mSpeed(RUN_SPEED_MIN){
	Rigidbody::InitRigidbody(PLAYER_RECT, MASS, true, true);
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
	mAnimation.LoadSprite("player-run");
	mAnimation.ScaleAnimationSprite(0.9, 0.9);
}

void Player::Update(uint32_t deltaTime){

	UpdateSpeed();
	SetRigidbodyVelocity();

	mLastPosition = GetPosition();
}

void Player::Draw(Screen& screen){
//	screen.Draw(mAARect, Color::Blue(), false, Color::Blue());
	mAnimation.Draw(screen, mAARect.GetCenterPoint());
}

void Player::MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& point, bool limitToEdge){

}

void Player::Run(signed int direction, bool released){

	// Set right or left key (depending on direction)
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

