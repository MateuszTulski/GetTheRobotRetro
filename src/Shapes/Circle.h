#ifndef SHAPES_CIRCLE_H_
#define SHAPES_CIRCLE_H_

#include "Shape.h"

class Circle: public Shape{
public:
	Circle();
	Circle(const Vec2D& center, float radius);

	inline void SetRadius(float radius) {mRadius = radius;}
	inline float GetRadius() const {return mRadius;}
	inline void MoveTo(const Vec2D& point) override {mPoints[0] = point;}

	inline Vec2D GetCenterPoint() const override {return mPoints[0];}

	bool Intersect(const Circle& otherCircle) const;
	bool ContainsPoint(const Vec2D& point) const;
private:
	float mRadius;
};


#endif /* SHAPES_CIRCLE_H_ */
