#include "AARectangle.h"

#include <iostream>

AARectangle::AARectangle(): AARectangle(Vec2D::Zero, Vec2D::Zero){};

AARectangle::AARectangle(const Vec2D& topLeft, const Vec2D& bottomRight){
	mPoints.push_back(topLeft);
	mPoints.push_back(bottomRight);
}

AARectangle::AARectangle(const Vec2D& topLeft, float width, float height){
	float x = topLeft.GetX() + width - 1;
	float y = topLeft.GetY() + height -1 ;
	mPoints.push_back(topLeft);
	mPoints.push_back(Vec2D(x, y));
}

AARectangle AARectangle::Inset(const AARectangle& rect, Vec2D& insets){
	return AARectangle(rect.GetTopLeft()+insets, rect.GetWidth() - 2*insets.GetX(), rect.GetHeight() - 2*insets.GetY());
}

bool AARectangle::Intersects(const AARectangle& other) const{

	// If any of this conditions is == true  ->  return Intersects FALSE
	bool left = (other.GetBottomRight().GetX() < GetTopLeft().GetX());
	bool top = (other.GetBottomRight().GetY() < GetTopLeft().GetY());
	bool right = (other.GetTopLeft().GetX() > GetBottomRight().GetX());
	bool bottom = (other.GetTopLeft().GetY() > GetBottomRight().GetY());


	if(left || top || right || bottom){
		return false;
	}
	return true;
}

bool AARectangle::ContainsPoint(const Vec2D& point) const{
	bool withinX = (point.GetX() < GetBottomRight().GetX() && point.GetX() > GetTopLeft().GetX());
	bool withinY = (point.GetY() > GetTopLeft().GetY() && point.GetY() < GetBottomRight().GetY());
	return (withinX && withinY);
}

float AARectangle::Area() const{
	float width = abs(GetBottomRight().GetX() - GetTopLeft().GetX());
	float height = abs(GetBottomRight().GetY() - GetTopLeft().GetY());

	return width * height;
}

void AARectangle::ScaleToPoint(const Vec2D& point, float scale)
{
	Vec2D topLeft, bottomRight;

	float topLeftNewDistance = scale * (mPoints[0].Distance(point));
	float bottomRightNewDistance = scale * (mPoints[1].Distance(point));

	Vec2D p1Direction (point.GetX()-mPoints[0].GetX(), point.GetY()-mPoints[0].GetY());
	Vec2D p2Direction (point.GetX()-mPoints[1].GetX(), point.GetY()-mPoints[1].GetY());

	std::cout << p1Direction << std::endl;
	std::cout << p2Direction << std::endl;

	mPoints[0] = point + (p1Direction.Normalize() * topLeftNewDistance);
	mPoints[1] = point + (p2Direction.Normalize() * bottomRightNewDistance);
}

void AARectangle::ScaleToCenter(float scale)
{
	Vec2D center = GetCenterPoint();
	ScaleToPoint(center, scale);
}

float AARectangle::GetWidth() const{
	return GetBottomRight().GetX() - GetTopLeft().GetX() + 1;
}

float AARectangle::GetHeight() const{
	return GetBottomRight().GetY() - GetTopLeft().GetY() + 1;
}

Vec2D AARectangle::GetCenterPoint() const{
	float xPos = (GetTopLeft().GetX()+GetBottomRight().GetX())/2;
	float yPos = (GetTopLeft().GetY()+GetBottomRight().GetY())/2;

	return Vec2D(xPos, yPos);
}

std::vector<Vec2D> AARectangle::GetPoints() const{
/* 	Return 4 points in vector
	0 ----- 1
	|		|
	|		|
	3 ----- 2
*/

	Vec2D p1 = GetTopLeft();
	Vec2D p2 = Vec2D(GetBottomRight().GetX(), GetTopLeft().GetY());
	Vec2D p3 = GetBottomRight();
	Vec2D p4 = Vec2D(GetTopLeft().GetX(), GetBottomRight().GetY());

	std::vector<Vec2D> points {p1, p2, p3, p4};
	return points;
}

void AARectangle::MoveTo(const Vec2D& point){

	float width = GetWidth();
	float height = GetHeight();

	SetTopLeft(point);
	SetBottomRight(Vec2D(point.GetX() + width - 1, point.GetY() + height - 1));
}
