#include "Camera.h"

Camera::Camera() : mPosition(Vec2D::Zero), mFollowOffset(Vec2D::Zero), mSpeed(DEFAULT_SPEED){
}

Camera::Camera(const Camera& other) : mPosition(other.mPosition), mSpeed(other.mSpeed)
{

}

Camera::Camera(Camera&& other) : mPosition(std::move(other.mPosition)), mSpeed(std::move(other.mSpeed))
{

}

void Camera::Init(Vec2D startPos)
{
	mPosition = startPos;
}

void Camera::Update(const Player& player)
{
	Vec2D newPoint(mPosition.GetX()+1, mPosition.GetY());
	mPosition = newPoint;
}
