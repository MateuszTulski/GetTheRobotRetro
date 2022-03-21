#include "Player.h"
#include "Color.h"
#include "Screen.h"

Player::Player(){
	Rigidbody::Init(PLAYER_RECT, MASS, true, true);
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
