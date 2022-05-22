#include "Robot.h"
#include "LevelFilesReader.h"
#include "LevelLoader.h"
#include "PursuitController.h"
#include <cassert>
#include <algorithm>

Robot::Robot() :
		mAnimation(),
		isRunning(true),
		pathIt(nullptr){
	mSpeed = RUN_SPEED_MIN;
	assert(LoadRobotAnimation() && "Couldn't load robot animation!");
}

bool Robot::Init(){

	bool loadAnim = LoadRobotAnimation();
	bool loadPath = LoadRobotPath();
	mPosition = Vec2D(100, 350);
	if(loadPath){
		pathIt = pathToFollow.begin();
		mPosition = *pathIt;
		mStartPosition = mPosition;
		pathIt++;
	}

	return loadAnim && loadPath;
}

void Robot::Restart(){
	pathIt = pathToFollow.begin();
	mPosition = mStartPosition;
}

void Robot::Update(const PursuitController& controller){
	mAnimation.Update();
	UpdateSpeed(controller.GetPlayerRobotDistance());
	Move();
}

void Robot::Draw(Screen& screen){
	mAnimation.Draw(screen, mPosition);
}

bool Robot::LoadRobotAnimation(){
	mAnimation.LoadSprite("robot-basic");
	mAnimation.SetFrameRate(5);
	mAnimation.SetLoopTime(true);

	mAnimation.SetVerticalAlign(AnimVerticalAlign::Bottom);
	mAnimation.SetHorizontalAlign(AnimHorizontalAlign::Right);

	mAnimation.Play();

	return true;
}

void Robot::UpdateSpeed(const float& distToPlayer){
	if(distToPlayer < MAX_SPEED_DIST){
		mSpeed = RUN_SPEED_MAX;
	}
	else if(distToPlayer > MIN_SPEED_DIST){
		mSpeed = RUN_SPEED_MIN;
	}
	else{
		float speedFactor = (distToPlayer - MAX_SPEED_DIST) / (MIN_SPEED_DIST - MAX_SPEED_DIST);
		mSpeed = (RUN_SPEED_MAX - RUN_SPEED_MIN) * (1-speedFactor);
	}
}

void Robot::Move(){
	if(pathIt!=pathToFollow.end()){
//		float distance = mPosition.Distance(*pathIt);
//		if(distance < PATH_POINT_MIN_DIST){
//			pathIt++;
//		}
//		float speed = mSpeed * App::Singleton().GetTime().DeltaTime();
//		mPosition.MoveTowards(*pathIt, speed);

		Vec2D nextPosition = mPosition;
		if(mPosition.GetX()+mSpeed > pathIt->GetX()){
			pathIt++;
		}
			float xOffset, yOffset;
			xOffset = mSpeed*App::Singleton().GetTime().DeltaTime();

			float xDistBetweenPoints = pathIt->GetX() - mPosition.GetX();
			float yDistBetweenPoints = pathIt->GetY() - mPosition.GetY();

			float offsetFactor = xOffset / xDistBetweenPoints;
			yOffset = yDistBetweenPoints * offsetFactor;

			nextPosition.SetX(mPosition.GetX()+xOffset);
			nextPosition.SetY(mPosition.GetY()+yOffset);

			mPosition = nextPosition;
	}
}

bool Robot::LoadRobotPath(){
	LevelFilesReader pathPoints;
	std::string fileName("level");
	if(pathPoints.LoadFile(fileName, LOT_Points, 'p')){
		std::vector<Vec2D> points = pathPoints.GetPoints();
		pathToFollow.reserve(points.size());
		if(points.size() > 0){
			for(auto p : points){
				Vec2D position(Vec2D(p.GetX()*LevelLoader::LEVEL_GRID_SIZE, p.GetY()*LevelLoader::LEVEL_GRID_SIZE));
				pathToFollow.emplace_back(position);
			}
		}
		// Sort the points
		sort(pathToFollow.begin(), pathToFollow.end(), [](const Vec2D& a, const Vec2D& b){
			return a.GetX() < b.GetX();
		});

		return true;
	}else{
		return false;
	}
}




