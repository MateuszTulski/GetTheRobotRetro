#ifndef SRC_GAMEOBJECTS_ROBOT_H_
#define SRC_GAMEOBJECTS_ROBOT_H_

#include "Rigidbody.h"
#include "App.h"
#include "Vec2D.h"
#include "Animation.h"
#include "Circle.h"

class PursuitController;

class Robot{
public:
	Robot();
	bool Init();

	void Restart();

	void Update(const PursuitController& controller);
	void Draw(Screen& screen);

	inline Vec2D GetPosition() const {return mPosition;}
	inline void SetStartPosition(const Vec2D& newPosition) {mPosition = newPosition;}

private:
	Vec2D mStartPosition;
	Vec2D mPosition;

	Animation mAnimation;
	bool isRunning;

	std::vector<Vec2D>::iterator pathIt;
	std::vector<Vec2D> pathToFollow;

	float mSpeed;
	const float RUN_SPEED_MIN = 80.0f;
	const float RUN_SPEED_MAX = 210.0f;

	const float MAX_SPEED_DIST = 10.0f;
	const float MIN_SPEED_DIST = 600.0f;

	const float PATH_POINT_MIN_DIST = 10.0f;

	const float WIDTH = 12;
	const float HEIGHT = 30;
	const AARectangle ROBOT_RECT = {Vec2D::Zero, WIDTH, HEIGHT};

	bool LoadRobotPath();
	bool LoadRobotAnimation();
	void UpdateSpeed(const float& distToPlayer);
	void Move();
};



#endif /* SRC_GAMEOBJECTS_ROBOT_H_ */
