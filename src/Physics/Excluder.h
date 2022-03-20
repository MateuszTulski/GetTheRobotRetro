#ifndef GAMES_EXCLUDER_H_
#define GAMES_EXCLUDER_H_

#include "AARectangle.h"
#include "BoundaryEdge.h"

class Excluder{
public:
	virtual ~Excluder(){};
	void Init(const AARectangle& rect, bool reverseNormals = false);
	bool HasCollided(const AARectangle& otherRect, BoundaryEdge& edges) const;
	Vec2D GetCollisionOffset(const AARectangle& otherRect) const;
	inline const AARectangle& GetAARectangle() const {return mAARect;}
	void MoveBy(const Vec2D& delta);
	void MoveTo(const Vec2D& point);
	const BoundaryEdge& GetEdge(EdgeType edge) const;

private:
	void SetUpEdges();
	AARectangle mAARect;
	BoundaryEdge mEdges[NUM_EDGES];
	bool mReverseNormals;
};

#endif /* GAMES_EXCLUDER_H_ */
