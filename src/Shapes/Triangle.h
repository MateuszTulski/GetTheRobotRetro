#ifndef SHAPES_TRIANGLE_H_
#define SHAPES_TRIANGLE_H_

#include "Shape.h"

class Triangle: public Shape{
public:
	Triangle();
	Triangle(Vec2D p1, Vec2D p2, Vec2D p3);

	inline void SetP1(const Vec2D& p1){mPoints[0] = p1;}
	inline void SetP2(const Vec2D& p2){mPoints[1] = p2;}
	inline void SetP3(const Vec2D& p3){mPoints[2] = p3;}

	inline Vec2D GetP1() const {return mPoints[0];}
	inline Vec2D GetP2() const {return mPoints[1];}
	inline Vec2D GetP3() const {return mPoints[2];}

	Vec2D GetCenterPoint() const override;

	float Area() const;

	bool ContainsPoint(const Vec2D& point) const;

	void MoveTo(const Vec2D& point) override;

private:
	float Area(const Vec2D& p1, const Vec2D& p2, const Vec2D& p3) const;
};


#endif /* SHAPES_TRIANGLE_H_ */
