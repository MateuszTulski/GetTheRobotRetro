#include "Robot.h"
#include <cassert>

Robot::Robot() : Robot(Vec2D::Zero){
}

Robot::Robot(const Vec2D& startPosition) :
	mPosition(startPosition),
	mAnimation(),
	isRunning(true),
	mSpeed(RUN_SPEED_MIN){

	assert(LoadRobotAnimation() && "Couldn't load robot animation!");
}

void Robot::Update(){

}

void Robot::Draw(Screen& screen){

}

Vec2D Robot::GetPosition() const{
	return Vec2D(mAARect.GetBottomRight().GetX() - WIDTH/2, mAARect.GetBottomRight().GetY() - HEIGHT/2);;
}

bool Robot::LoadRobotAnimation(){


	return true;
}

void Robot::UpdateSpeed(){

}
