#include "Player.h"
#include "Color.h"
#include "Screen.h"

Player::Player() : mJumpPressed(false){
	Rigidbody::InitRigidbody(PLAYER_RECT, MASS, true, true);
}

void Player::Init(const Vec2D& startPosition){
	// Start position is BOTTOM MIDDLE
	SetPosition(startPosition);
	SetGravityScale(1.5f);
}

void Player::Update(uint32_t deltaTime){
	if(RIGHT_KEY_PRESSED && !LEFT_KEY_PRESSED){
		SetHorizontalVelocity(200);
	}
	else if(LEFT_KEY_PRESSED && !RIGHT_KEY_PRESSED)
	{
		SetHorizontalVelocity(-200);
	}
	else
	{
		SetHorizontalVelocity(0);
	}

}

void Player::Draw(Screen& screen){
	screen.Draw(mAARect, Color::Blue(), true, Color::Blue());
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
