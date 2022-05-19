#include "Robot.h"
#include "LevelFilesReader.h"
#include "LevelLoader.h"
#include <cassert>
#include <algorithm>

Robot::Robot() : Robot(Vec2D::Zero){
}

Robot::Robot(const Vec2D& startPosition) :
	mPosition(startPosition),
	mAnimation(),
	isRunning(true),
	pathIt(nullptr){
		mSpeed = RUN_SPEED_MIN;
		assert(LoadRobotAnimation() && "Couldn't load robot animation!");
}

bool Robot::Init(const Vec2D& startPosition){

	bool loadAnim = LoadRobotAnimation();
	bool loadPath = LoadRobotPath();
	mPosition = Vec2D(100, 350);
	if(loadPath){
		pathIt = pathToFollow.begin();
		mPosition = *pathIt;
		pathIt++;
	}

	return loadAnim && loadPath;
}

void Robot::Update(){
	mAnimation.Update();
	UpdateSpeed();
	MoveTowardsNextPoint();
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

void Robot::UpdateSpeed(){

}

void Robot::MoveTowardsNextPoint(){
	if(pathIt!=pathToFollow.end()){
		float distance = mPosition.Distance(*pathIt);
		if(distance < PATH_POINT_MIN_DIST){
			pathIt++;
		}
		float speed = mSpeed * App::Singleton().GetTime().DeltaTime();
		mPosition.MoveTowards(*pathIt, speed);
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




