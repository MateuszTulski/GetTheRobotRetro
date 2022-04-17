#include "Camera.h"

Camera::Camera() : mPosition(Vec2D::Zero), mFollowOffset(Vec2D::Zero), maxSpeed(DEFAULT_SPEED*2.3f), minSpeed(DEFAULT_SPEED*.1f){
}

Camera::Camera(const Camera& other) : mPosition(other.mPosition), maxSpeed(other.maxSpeed), minSpeed(other.minSpeed)
{

}

Camera::Camera(Camera&& other) : mPosition(std::move(other.mPosition)), maxSpeed(std::move(other.maxSpeed)), minSpeed(std::move(other.minSpeed))
{

}

void Camera::Init(Vec2D startPos)
{
	mPosition = startPos;
}

void Camera::Update(const Player& player)
{
	Vec2D desiredPosition(player.GetAARectangle().GetTopLeft().GetX() + mFollowOffset.GetX(), player.GetAARectangle().GetTopLeft().GetY() + mFollowOffset.GetY());

	Vec2D moveDirection = desiredPosition - mPosition;
	moveDirection = moveDirection.Normalize();

	if(desiredPosition != mPosition)
	{
		float distance = mPosition.Distance(desiredPosition);
		if(distance < maxSpeed)
		{
			mPosition = desiredPosition;
		}
		else
		{
			float speedDistanceFactor = distance / DISTANCE_SPEED_FACTOR;
			if(speedDistanceFactor > 1)
			{
				mPosition += moveDirection * maxSpeed;
			}
			else
			{
				float speed = ((maxSpeed - minSpeed) * speedDistanceFactor) + minSpeed;
				mPosition += moveDirection * speed;
			}
		}
//		std::cout << mPosition << std::endl;
	}
}
