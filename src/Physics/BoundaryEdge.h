#ifndef GAMES_BOUNDARYEDGE_H_
#define GAMES_BOUNDARYEDGE_H_

#include "Vec2D.h"
#include "Line2D.h"

enum EdgeType {
	BOTTOM_EDGE = 0,
	TOP_EDGE,
	LEFT_EDGE,
	RIGHT_EDGE,
	NUM_EDGES
};

static const Vec2D DIR_UP = {0, -1};
static const Vec2D DIR_DOWN = {0, 1};
static const Vec2D DIR_LEFT = {-1, 0};
static const Vec2D DIR_RIGHT = {1, 0};

struct BoundaryEdge{
	Vec2D normal;
	Line2D edge;
};


#endif /* GAMES_BOUNDARYEDGE_H_ */
