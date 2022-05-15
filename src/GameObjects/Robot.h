#ifndef SRC_GAMEOBJECTS_ROBOT_H_
#define SRC_GAMEOBJECTS_ROBOT_H_

#include "Rigidbody.h"
#include "Vec2D.h"
#include "Animation.h"

class Robot : public Rigidbody{
public:
	Robot();
	Robot(const Vec2D& startPosition);

	void Update();
	void Draw(Screen& screen);

	Vec2D GetPosition() const;

private:
	Vec2D mPosition;
	Animation mAnimation;
	bool isRunning;

	float mSpeed;
	const float RUN_SPEED_MIN = 30.0f;
	const float RUN_SPEED_MAX = 160.0f;

	const float WIDTH = 12;
	const float HEIGHT = 30;
	const AARectangle ROBOT_RECT = {Vec2D::Zero, WIDTH, HEIGHT};

	bool LoadRobotAnimation();
	void UpdateSpeed();
};



#endif /* SRC_GAMEOBJECTS_ROBOT_H_ */
