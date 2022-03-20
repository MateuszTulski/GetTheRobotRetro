#include "Circle.h"
#include "Utils.h"

Circle::Circle(): Circle(Vec2D::Zero, 0){
}

Circle::Circle(const Vec2D& center, float radius): mRadius(radius){
	mPoints.push_back(center);
}

bool Circle::Intersect(const Circle& otherCircle) const{
	return (GetCenterPoint().Distance(otherCircle.GetCenterPoint()) < (GetRadius() + otherCircle.GetRadius()));
}
bool Circle::ContainsPoint(const Vec2D& point) const{
	return IsLessThanOrEqual(GetCenterPoint().Distance(point), GetRadius());
}
