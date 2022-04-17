#ifndef _VEC2D_H_
#define _VEC2D_H_

#include <ostream>

class Vec2D{
private:
	float mX, mY;
public:
	Vec2D(): mX{0}, mY{0}{};
	Vec2D(float x, float y): mX{x}, mY{y}{}
	~Vec2D(){};

	static const Vec2D Zero;

	inline float GetX() const{return mX;}
	inline float GetY() const{return mY;}

	inline void SetX(float x) {mX = x;}
	inline void SetY(float y) {mY = y;}

	bool operator==(const Vec2D &rhs) const;
	bool operator!=(const Vec2D &rhs) const;

	Vec2D operator-() const;
	Vec2D operator*(const float &rhs) const;
	Vec2D operator/(const float &rhs) const;
	Vec2D operator*=(const float &rhs);
	Vec2D operator/=(const float &rhs);

	Vec2D operator+(const Vec2D &rhs) const;
	Vec2D operator-(const Vec2D &rhs) const;
	Vec2D operator+=(const Vec2D &rhs);
	Vec2D operator-=(const Vec2D &rhs);

	Vec2D operator=(const Vec2D &rhs);

	///// CONTINUE WORK HERE

	Vec2D GetUnitVec() const;
	Vec2D& Normalize();
	Vec2D ProjectOnTo(const Vec2D& vec2) const;

	float Mag() const;
	float Mag2() const;

	float Distance(const Vec2D& vec2) const;
	float Dot(const Vec2D& vec2) const;
	float AngleBetween(const Vec2D& vec2) const;
	float AngleBetweenDeg(const Vec2D& vec2) const;
	Vec2D Reflect(const Vec2D& normal) const;

	void Rotate(float angle, const Vec2D& aroundPoint);
	void RotateDegrees(float angle, const Vec2D& aroundPoint);
	Vec2D RotationResult(float angle, const Vec2D& aroundPoint) const;

	friend std::ostream& operator<<(std::ostream& os, const Vec2D& vec);
	friend Vec2D operator*(float scalar, const Vec2D& vec);
};

#endif
