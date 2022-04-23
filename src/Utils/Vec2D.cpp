#include <iostream>
#include "Vec2D.h"
#include "Utils.h"
#include <cmath>
#include <math.h>

const Vec2D Vec2D::Zero;

std::ostream& operator<<(std::ostream& os, const Vec2D& vec){
	os << "Vec2D ( X:"<< vec.mX << " Y:"<< vec.mY << " )\n";
	return os;
}
Vec2D operator*(float scalar, const Vec2D& vec){
	return vec*scalar;
}

bool Vec2D::operator==(const Vec2D &rhs) const{
	bool x = IsEqual(mX, rhs.mX);
	bool y = IsEqual(mY, rhs.mY);

	return (x && y);
}
bool Vec2D::operator!=(const Vec2D &rhs) const{
	return !(*this==rhs);
}

Vec2D Vec2D::operator-() const{
	return Vec2D(-mX, -mY);
}
Vec2D Vec2D::operator*(const float &rhs) const{
	float newX = mX * rhs;
	float newY = mY * rhs;
	return Vec2D(newX, newY);
}
Vec2D Vec2D::operator*=(const float &rhs){
	this->mX *= rhs;
	this->mY *= rhs;
	return *this;
}
Vec2D Vec2D::operator/(const float &rhs) const{
	if(rhs < EPSILON){
		return Vec2D(0, 0);
	}
	float newX = mX / rhs;
	float newY = mY / rhs;
	return Vec2D(newX, newY);
}
Vec2D Vec2D::operator/=(const float &rhs){
	this->mX /= rhs;
	this->mY /= rhs;
	return *this;
}
Vec2D Vec2D::operator+(const Vec2D &rhs) const{
	float newX = this->mX + rhs.mX;
	float newY = this->mY + rhs.mY;
	return Vec2D(newX, newY);
}
Vec2D Vec2D::operator+=(const Vec2D &rhs){
	this->mX += rhs.mX;
	this->mY += rhs.mY;
	return *this;
}

Vec2D Vec2D::operator-(const Vec2D &rhs) const{
	float newX = this->mX - rhs.mX;
	float newY = this->mY - rhs.mY;
	return Vec2D(newX, newY);
}
Vec2D Vec2D::operator-=(const Vec2D &rhs){
	this->mX -= rhs.mX;
	this->mY -= rhs.mY;
	return *this;
}

Vec2D Vec2D::operator=(const Vec2D &rhs){
	this->mX = rhs.mX;
	this->mY = rhs.mY;
	return *this;
}

Vec2D Vec2D::GetUnitVec() const{
	return *this / Mag();
}
Vec2D& Vec2D::Normalize(){
	float mag = Mag();
	if(mag < EPSILON){
		return *this;
	}
	*this /= mag;
	return *this;
}
Vec2D Vec2D::ProjectOnTo(const Vec2D& vec2) const{
	Vec2D unitVec2 = vec2.GetUnitVec();
	float dot = Dot(unitVec2);
	return unitVec2 * dot;
}
float Vec2D::Distance(const Vec2D& vec2) const{
	return (vec2 - *this).Mag();
}
float Vec2D::Dot(const Vec2D& vec2) const{
	return mX * vec2.mX + mY * vec2.mY;
}
float Vec2D::AngleBetween(const Vec2D& vec2) const{
	return acosf(GetUnitVec().Dot(vec2.GetUnitVec()));
}
float Vec2D::AngleBetweenDeg(const Vec2D& vec2) const{
	float deg = AngleBetween(vec2) * (180.0/3.141592653589793238463);
	return deg;
}
Vec2D Vec2D::Reflect(const Vec2D& normal) const{
	//v - 2(v dot n)n
	return *this - 2 * ProjectOnTo(normal);
}
float Vec2D::Mag2() const{
	return Dot(*this);
}
float Vec2D::Mag() const{
	return sqrt(Mag2());	// Length of the vector ( P0 -> (0,0) | P1 -> mVec2D )
}
void Vec2D::RotateDegrees(float angle, const Vec2D& aroundPoint){
	float rad = angle * (3.141592653589793238463/180.0);
	Rotate(rad, aroundPoint);
}
void Vec2D::Rotate(float angle, const Vec2D& aroundPoint){
	float cosine = cosf(angle);
	float sine = sinf(angle);

	Vec2D thisVec{mX, mY};
	thisVec -= aroundPoint;

	float rotX = thisVec.mX * cosine - thisVec.mY * sine;
	float rotY = thisVec.mX * sine + thisVec.mY * cosine;

	Vec2D rot{rotX, rotY};
	*this = rot + aroundPoint;
}
Vec2D Vec2D::RotationResult(float angle, const Vec2D& aroundPoint) const{
	float cosine = cosf(angle);
	float sine = sinf(angle);

	Vec2D thisVec{mX, mY};
	thisVec -= aroundPoint;

	float rotX = thisVec.mX * cosine - thisVec.mY * sine;
	float rotY = thisVec.mX * sine + thisVec.mY * cosine;

	Vec2D rot{rotX, rotY};
	return rot + aroundPoint;
}
