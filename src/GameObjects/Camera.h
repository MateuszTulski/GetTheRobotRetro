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

	inline Vec2D GetCameraPosition() const { return mPosition; }

	inline void SetCameraPosition(const Vec2D& pos) { mPosition = pos; }
	inline void SetCameraSpeed(const float& speed) { mSpeed = speed ; }

	inline void SetFollowOffset(const Vec2D& offset) { mFollowOffset = offset; }

private:
	const float DEFAULT_SPEED = 30;

	Vec2D mPosition;	// Camera top left corner position
	Vec2D mFollowOffset;
	float mSpeed;
	bool followPlayer = true;
};


#endif /* SRC_GAMEOBJECTS_CAMERA_H_ */
