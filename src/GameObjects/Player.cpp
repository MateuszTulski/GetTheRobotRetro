#include "Player.h"
#include "Color.h"
#include "Screen.h"

Player::Player(){
	Rigidbody::Init(PLAYER_RECT, MASS, true, true);
}

void Player::Init(const Vec2D& startPosition){
	// Start position is BOTTOM MIDDLE
	SetPosition(startPosition);
}

void Player::Update(uint32_t deltaTime){

}

void Player::Draw(Screen& screen){
	screen.Draw(mAARect, Color::Blue(), true, Color::Blue());
}

void Player::MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& point, bool limitToEdge){

}

void Player::Run(){

}

void Player::Jump(const BoundaryEdge& edge){

}

void Player::SetPosition(Vec2D bottomMiddlePoint){
	Vec2D newPos = bottomMiddlePoint - Vec2D(HEIGHT, WIDTH/2);
	mAARect.MoveTo(newPos);
}
