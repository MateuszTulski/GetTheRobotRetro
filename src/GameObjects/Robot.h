#ifndef SRC_GAMEOBJECTS_ROBOT_H_
#define SRC_GAMEOBJECTS_ROBOT_H_

#include "Rigidbody.h"
#include "App.h"
#include "Vec2D.h"
#include "Animation.h"

class Robot{
public:
	Robot();
	Robot(const Vec2D& startPosition);
	bool Init(const Vec2D& startPosition);

	void Update();
	void Draw(Screen& screen);

	inline Vec2D GetPosition() const {return mPosition;}
	inline void SetStartPosition(const Vec2D& newPosition) {mPosition = newPosition;}

private:
	Vec2D mPosition;
	Animation mAnimation;
	bool isRunning;

	std::vector<Vec2D>::iterator pathIt;
	std::vector<Vec2D> pathToFollow;

	float mSpeed;
	const float RUN_SPEED_MIN = 50.0f;
	const float RUN_SPEED_MAX = 160.0f;

	const float PATH_POINT_MIN_DIST = 10.0f;

	const float WIDTH = 12;
	const float HEIGHT = 30;
	const AARectangle ROBOT_RECT = {Vec2D::Zero, WIDTH, HEIGHT};

	bool LoadRobotPath();
	bool LoadRobotAnimation();
	void UpdateSpeed();
	void MoveTowardsNextPoint();
};



#endif /* SRC_GAMEOBJECTS_ROBOT_H_ */
