#ifndef GAMES_EXCLUDER_H_
#define GAMES_EXCLUDER_H_

#include "AARectangle.h"
#include "BoundaryEdge.h"

class Excluder{

public:
	virtual ~Excluder(){};
	void Init(const AARectangle& rect, bool reverseNormals = false);

	bool HasCollided(const Excluder& otherRect, BoundaryEdge& edges) const;
	Vec2D GetCollisionOffset(const Excluder& otherRect) const;

	inline const AARectangle& GetAARectangle() const {return mAARect;}
	void MoveBy(const Vec2D& delta);
	void MoveTo(const Vec2D& point);
	const BoundaryEdge& GetEdge(EdgeType edge) const;

protected:
	AARectangle mAARect;
private:

	void SetUpEdges();
	BoundaryEdge mEdges[NUM_EDGES];
	bool mReverseNormals;
};

#endif /* GAMES_EXCLUDER_H_ */
