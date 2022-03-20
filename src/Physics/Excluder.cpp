#include "Excluder.h"
#include "Utils.h"
#include <cassert>
#include <iostream>

void Excluder::Init(const AARectangle& rect, bool reverseNormals){
	mAARect = rect;
	mReverseNormals = reverseNormals;
	SetUpEdges();
}

bool Excluder::HasCollided(const AARectangle& otherRect, BoundaryEdge& edge) const{
	// edge is reference because we want to change it on the end of this function

	if(mAARect.Intersects(otherRect)){
//			+-------+
//			|	+---|---+
//			+---|---+	|
//				+-------+

		float yMin = mAARect.GetTopLeft().GetY() >= otherRect.GetTopLeft().GetY() ? mAARect.GetTopLeft().GetY() : otherRect.GetTopLeft().GetY();
		float yMax = mAARect.GetBottomRight().GetY() >= otherRect.GetBottomRight().GetY() ? otherRect.GetBottomRight().GetY() : mAARect.GetBottomRight().GetY();

		float xMin = mAARect.GetTopLeft().GetX() <= otherRect.GetTopLeft().GetX() ? otherRect.GetTopLeft().GetX() : mAARect.GetTopLeft().GetX();
		float xMax = mAARect.GetBottomRight().GetX() <= otherRect.GetBottomRight().GetX() ? mAARect.GetBottomRight().GetX() : otherRect.GetBottomRight().GetX();

		// Check which distance is bigger -> X of Y
		float yDist = yMax - yMin;
		float xDist = xMax - xMin;

		if(xDist > yDist){
			// Collision detected on top/bottom edge
			if(mAARect.GetCenterPoint().GetY() <= otherRect.GetCenterPoint().GetY()){
				// mAARect is higher -> bottom collision
				edge = mEdges[BOTTOM_EDGE];
			}else{
				// mAARect is below -> top collision
				edge = mEdges[TOP_EDGE];
			}
		}else{
			// Collision detected on left/right edge
			if(mAARect.GetCenterPoint().GetX() <= otherRect.GetCenterPoint().GetX()){
				// mAARect is on the left -> right collision
				edge = mEdges[RIGHT_EDGE];
			}else{
				// mAARect is on the right -> left collison
				edge = mEdges[LEFT_EDGE];
			}
		}

		return true;
	}

	return false;
}

Vec2D Excluder::GetCollisionOffset(const AARectangle& otherRect) const{

	// How deep the objects overlapped? Return overlapping offset

	BoundaryEdge edge;
	Vec2D offset;

	if(HasCollided(otherRect, edge)){
		float yMin = mAARect.GetTopLeft().GetY() >= otherRect.GetTopLeft().GetY() ? mAARect.GetTopLeft().GetY() : otherRect.GetTopLeft().GetY();
		float yMax = mAARect.GetBottomRight().GetY() >= otherRect.GetBottomRight().GetY() ? otherRect.GetBottomRight().GetY() : mAARect.GetBottomRight().GetY();

		float xMin = mAARect.GetTopLeft().GetX() <= otherRect.GetTopLeft().GetX() ? otherRect.GetTopLeft().GetX() : mAARect.GetTopLeft().GetX();
		float xMax = mAARect.GetBottomRight().GetX() <= otherRect.GetBottomRight().GetX() ? mAARect.GetBottomRight().GetX() : otherRect.GetBottomRight().GetX();

		// Check which distance is bigger -> X of Y
		float yDist = yMax - yMin;
		float xDist = xMax - xMin;

		// Check normal vector -> horizontal of vertical
		if(!IsEqual(edge.normal.GetY(), 0)){
			offset = (yDist + 1) * edge.normal;
		}else{
			offset = (xDist + 1) * edge.normal;
		}
	}
	return offset;
}

void Excluder::MoveBy(const Vec2D& delta){
	mAARect.MoveBy(delta);
	SetUpEdges();
}

void Excluder::MoveTo(const Vec2D& point){
	mAARect.MoveTo(point);
	SetUpEdges();
}

const BoundaryEdge& Excluder::GetEdge(EdgeType edge) const{
	assert(edge != NUM_EDGES);
	return mEdges[edge];
}

void Excluder::SetUpEdges(){
/*	AARect points
 	0---1
	3---2
 */
	const std::vector<Vec2D>& points = mAARect.GetPoints();

	mEdges[TOP_EDGE].edge = {points[0], points[1]};
	mReverseNormals ? mEdges[TOP_EDGE].normal = DIR_DOWN : mEdges[TOP_EDGE].normal = DIR_UP;

	mEdges[RIGHT_EDGE].edge = {points[1], points[2]};
	mReverseNormals ? mEdges[RIGHT_EDGE].normal = DIR_LEFT : mEdges[RIGHT_EDGE].normal = DIR_RIGHT;

	mEdges[BOTTOM_EDGE].edge = {points[2], points[3]};
	mReverseNormals ? mEdges[BOTTOM_EDGE].normal = DIR_UP : mEdges[BOTTOM_EDGE].normal = DIR_DOWN;

	mEdges[LEFT_EDGE].edge = {points[3], points[0]};
	mReverseNormals ? mEdges[LEFT_EDGE].normal = DIR_RIGHT : mEdges[LEFT_EDGE].normal = DIR_LEFT;

}
