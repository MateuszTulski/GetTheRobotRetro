#include "Excluder.h"
#include "Utils.h"
#include <cassert>
#include <iostream>

void Excluder::Init(const AARectangle& rect, bool reverseNormals){

	mAARect = rect;
	mReverseNormals = reverseNormals;
	SetUpEdges();
}

bool Excluder::HasCollided(const Excluder& otherExcluder, BoundaryEdge& outEdge) const{
	

	if(mAARect.Intersects(otherExcluder.mAARect)){
//			 +-------+
//			A|	 +---|---+
//			 +---|---+	 |B
//				 +-------+

		float yMin = mAARect.GetTopLeft().GetY() >= otherExcluder.mAARect.GetTopLeft().GetY() ? mAARect.GetTopLeft().GetY() : otherExcluder.mAARect.GetTopLeft().GetY();
		float yMax = mAARect.GetBottomRight().GetY() >= otherExcluder.mAARect.GetBottomRight().GetY() ? otherExcluder.mAARect.GetBottomRight().GetY() : mAARect.GetBottomRight().GetY();

		float xMin = mAARect.GetTopLeft().GetX() <= otherExcluder.mAARect.GetTopLeft().GetX() ? otherExcluder.mAARect.GetTopLeft().GetX() : mAARect.GetTopLeft().GetX();
		float xMax = mAARect.GetBottomRight().GetX() <= otherExcluder.mAARect.GetBottomRight().GetX() ? mAARect.GetBottomRight().GetX() : otherExcluder.mAARect.GetBottomRight().GetX();

		// Check which distance is bigger -> X of Y
		float yDist = yMax - yMin;
		float xDist = xMax - xMin;

		if(xDist > yDist){
			// Collision detected on HORIZONTAL edge
			if(mAARect.GetCenterPoint().GetY() <= otherExcluder.mAARect.GetCenterPoint().GetY())
			{
//				outEdge = otherExcluder.mEdges[BOTTOM_EDGE];
				outEdge = otherExcluder.mEdges[TOP_EDGE];
			}
			else
			{
//				outEdge = otherExcluder.mEdges[TOP_EDGE];
				outEdge = otherExcluder.mEdges[BOTTOM_EDGE];
			}
		}
		else
		{
			// Collision detected on VERTICAL edge
			if(mAARect.GetCenterPoint().GetX() <= otherExcluder.mAARect.GetCenterPoint().GetX())
			{
				outEdge = otherExcluder.mEdges[LEFT_EDGE];
//				outEdge = otherExcluder.mEdges[RIGHT_EDGE];
			}
			else
			{
				outEdge = otherExcluder.mEdges[RIGHT_EDGE];
//				outEdge = otherExcluder.mEdges[LEFT_EDGE];
			}
		}

		return true;
	}

	return false;
}

Vec2D Excluder::GetCollisionOffset(const Excluder& otherExcluder) const{

	// How deep the objects overlapped? Return overlapping offset

	BoundaryEdge outEdge;
	Vec2D offset;

	if(HasCollided(otherExcluder, outEdge)){
		float yMin = mAARect.GetTopLeft().GetY() >= otherExcluder.mAARect.GetTopLeft().GetY() ? mAARect.GetTopLeft().GetY() : otherExcluder.mAARect.GetTopLeft().GetY();
		float yMax = mAARect.GetBottomRight().GetY() >= otherExcluder.mAARect.GetBottomRight().GetY() ? otherExcluder.mAARect.GetBottomRight().GetY() : mAARect.GetBottomRight().GetY();

		float xMin = mAARect.GetTopLeft().GetX() <= otherExcluder.mAARect.GetTopLeft().GetX() ? otherExcluder.mAARect.GetTopLeft().GetX() : mAARect.GetTopLeft().GetX();
		float xMax = mAARect.GetBottomRight().GetX() <= otherExcluder.mAARect.GetBottomRight().GetX() ? mAARect.GetBottomRight().GetX() : otherExcluder.mAARect.GetBottomRight().GetX();

		// Check which distance is bigger -> X of Y
		float yDist = yMax - yMin;
		float xDist = xMax - xMin;

		// Check normal vector -> horizontal of vertical
		if(!IsEqual(outEdge.normal.GetY(), 0))
		{
			offset = (yDist + 1) * outEdge.normal;
		}else
		{
			offset = (xDist + 1) * outEdge.normal;
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
 	0-------1
 	|		|
	3-------2
 */
	const std::vector<Vec2D>& points = mAARect.GetPoints();

	mEdges[TOP_EDGE].edge = {points[0], points[1]};
	mReverseNormals ? mEdges[TOP_EDGE].normal = DIR_DOWN : mEdges[TOP_EDGE].normal = DIR_UP;

	mEdges[RIGHT_EDGE].edge = {points[1], points[2]};
	mReverseNormals ? mEdges[RIGHT_EDGE].normal = DIR_LEFT : mEdges[RIGHT_EDGE].normal = DIR_RIGHT;

	mEdges[BOTTOM_EDGE].edge = {points[3], points[2]};
	mReverseNormals ? mEdges[BOTTOM_EDGE].normal = DIR_UP : mEdges[BOTTOM_EDGE].normal = DIR_DOWN;

	mEdges[LEFT_EDGE].edge = {points[0], points[3]};
	mReverseNormals ? mEdges[LEFT_EDGE].normal = DIR_RIGHT : mEdges[LEFT_EDGE].normal = DIR_LEFT;

}
