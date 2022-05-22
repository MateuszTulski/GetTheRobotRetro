#ifndef SRC_GAMEOBJECTS_CAMERA_H_
#define SRC_GAMEOBJECTS_CAMERA_H_

#include "Vec2D.h"
#include "Player.h"
#include <memory>


class Camera {
public:
	Camera();

	Camera(const Camera& other);
	Camera(Camera&& other);

	void Init(Vec2D startPos = Vec2D::Zero);
	void Update(const Player& player);

	void RestartCamera();

	inline Vec2D GetCameraPosition() const { return mPosition; }

	inline void SetCameraPosition(const Vec2D& pos) { mPosition = pos; }
	inline void SetCameraSpeed(const float& speed) { maxSpeed = speed ; }

	inline void SetFollowOffset(const Vec2D& offset) { mFollowOffset = offset; }

private:
	const float DEFAULT_SPEED = 1.6f;
	const float DISTANCE_SPEED_FACTOR = 100.0f;

	float mSpeed(float distance);

	Vec2D mStartPosition;
	Vec2D mPosition;	// Camera top left corner position
	Vec2D mFollowOffset;
	float maxSpeed;
	float minSpeed;
	bool followPlayer = true;
};


#endif /* SRC_GAMEOBJECTS_CAMERA_H_ */
