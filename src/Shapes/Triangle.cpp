#include "Triangle.h"
#include <cmath>
#include <iostream>
#include "Utils.h"

Triangle::Triangle(): Triangle(Vec2D::Zero, Vec2D::Zero, Vec2D::Zero){}
Triangle::Triangle(Vec2D p1, Vec2D p2, Vec2D p3){
	mPoints.push_back(p1);
	mPoints.push_back(p2);
	mPoints.push_back(p3);
}

Vec2D Triangle::GetCenterPoint() const{
	float xPos = (mPoints[0].GetX() + mPoints[1].GetX() + mPoints[2].GetX())/3.0f;
	float yPos = (mPoints[0].GetY() + mPoints[1].GetY() + mPoints[2].GetY())/3.0f;
	return Vec2D(xPos, yPos);
}

float Triangle::Area() const{
	return Area(GetP1(), GetP2(), GetP3());
}
float Triangle::Area(const Vec2D& p1, const Vec2D& p2, const Vec2D& p3) const{

	float part1 = (p1.GetX()*p2.GetY())-(p2.GetX()*p1.GetY());
	float part2 = (p2.GetX()*p3.GetY())-(p3.GetX()*p2.GetY());
	float part3 = (p3.GetX()*p1.GetY())-(p1.GetX()*p3.GetY());

	float area = fabs(part1+part2+part3)/2.0f;
	return area;
}
bool Triangle::ContainsPoint(const Vec2D& point) const{

	float area1 = Area(point, GetP2(), GetP3());
	float area2 = Area(GetP1(), point, GetP3());
	float area3 = Area(GetP1(), GetP2(), point);

	return IsEqual(area1+area2+area3, Area());
}

void Triangle::MoveTo(const Vec2D& point){
	Vec2D delta = point - GetCenterPoint();
	MoveBy(point);
}
