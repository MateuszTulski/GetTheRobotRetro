#ifndef SHAPES_AARECTANGLE_H_
#define SHAPES_AARECTANGLE_H_

#include "Shape.h"

class AARectangle: public Shape{
public:

	AARectangle();
	AARectangle(const Vec2D& topLeft, const Vec2D& bottomRight);
	AARectangle(const Vec2D& topLeft, float width, float height);
	~AARectangle(){}

	static AARectangle Inset(const AARectangle& rect, Vec2D& insets);

	inline void SetTopLeft(const Vec2D& topLeft){mPoints[0] = topLeft;}
	inline void SetBottomRight(const Vec2D& bottomRight){mPoints[1] = bottomRight;}

	inline Vec2D GetTopLeft() const {return mPoints[0];}
	inline Vec2D GetBottomRight() const {return mPoints[1];}

	float GetWidth() const;
	float GetHeight() const;

	bool Intersects(const AARectangle& other) const;
	bool ContainsPoint(const Vec2D& point) const;

	float Area() const;

	Vec2D GetCenterPoint() const override;
	std::vector<Vec2D> GetPoints() const override;
	void MoveTo(const Vec2D& point) override;

};


#endif /* SHAPES_AARECTANGLE_H_ */
