#include "App.h"
#include "Rigidbody.h"
#include "PhysicsWorld.h"
#include "Utils.h"
#include <iostream>

int Rigidbody::InitializedRigidbody = 0;

Rigidbody::Rigidbody() : Rigidbody(AARectangle(Vec2D::Zero, Vec2D::Zero), 0, true, true){
}

Rigidbody::Rigidbody(AARectangle rect, float mass, bool useGravity, bool isCollider) : mVelocity(Vec2D::Zero), mUseGravity(useGravity), mIsCollider(isCollider), mMass(mass)
{
	InitializedRigidbody++;
	mID = InitializedRigidbody;
	Excluder::Init(rect);
}

Rigidbody::Rigidbody(const Rigidbody& other) : mVelocity(Vec2D::Zero), mUseGravity(std::move(other.mUseGravity)), mIsCollider(std::move(other.mIsCollider)), mMass(std::move(other.mMass))
{
	mID = other.GetRigidbodyID();
}

Rigidbody::~Rigidbody()
{

}

bool Rigidbody::operator==(const Rigidbody& other)
{
	return this->mID == other.GetRigidbodyID();
}

void Rigidbody::InitRigidbody(AARectangle rect, float mass, bool useGravity, bool isCollider){

	mUseGravity = useGravity;
	mIsCollider = isCollider;
	mMass = mass;
	Excluder::Init(rect);
	// Add this Rigidbody to the world
	if(mUseGravity){
		PhysicsWorld::Singleton().AddKinematicRigidbody(this);
	}else{
		PhysicsWorld::Singleton().AddStaticRigidbody(this);
	}

}

void Rigidbody::UpdateRigdbody(uint32_t deltaTime){
	if(!mUseGravity){
		return;
	}
	Vec2D finalOffset = mVelocity * App::Singleton().GetTime().DeltaTime();

	BoundaryEdge outObstacleEdge;

	// Checking ACTUAL and POTENTIAL collisions
	for(Rigidbody* otherRigidbody : PhysicsWorld::Singleton().GetAllRigidbodyObjects()){
		if(otherRigidbody->IsCollider() && mID != otherRigidbody->GetRigidbodyID())
		{
			// ACTUAL - Check if rigidbody is already colliding
			if(HasCollided(*otherRigidbody, outObstacleEdge))
			{
				MakeFlushWithEdge(outObstacleEdge);
				StopOnObstacle(outObstacleEdge.normal);
				ResetOffsetOnObstacle(finalOffset, outObstacleEdge);
			}

			// POTENTIAL - Check possible collision after finalOffset
			Excluder offsetGhost;
			offsetGhost.Init(GetAARectangle());
			offsetGhost.MoveBy(finalOffset);

			if(offsetGhost.HasCollided(*otherRigidbody, outObstacleEdge))
			{
				StopOnObstacle(outObstacleEdge.normal);
				ResetOffsetOnObstacle(finalOffset, outObstacleEdge);
			}
		}
	}

	MoveBy(finalOffset);
}

void Rigidbody::ResetOffsetOnObstacle(Vec2D& offset, const BoundaryEdge& obstacleEdge){

	if(!IsEqual(obstacleEdge.normal.GetX(), 0))
	{
		offset.SetX(0);
	}
	if(!IsEqual(obstacleEdge.normal.GetY(), 0))
	{
		offset.SetY(0);
	}
}

void Rigidbody::MakeFlushWithEdge(const BoundaryEdge& edge){

	if(edge.normal == DIR_UP)
	{
		MoveTo(Vec2D(mAARect.GetTopLeft().GetX(), edge.edge.GetP0().GetY() - mAARect.GetHeight() - COLLISION_OFFSET));
	}
	else if(edge.normal == DIR_DOWN)
	{
		MoveTo(Vec2D(mAARect.GetTopLeft().GetX(), edge.edge.GetP0().GetY() + COLLISION_OFFSET));
	}
	else if(edge.normal == DIR_LEFT)
	{
		MoveTo(Vec2D(edge.edge.GetP0().GetX() - mAARect.GetWidth() - COLLISION_OFFSET, mAARect.GetTopLeft().GetY()));
	}
	else if(edge.normal == DIR_RIGHT)
	{
		MoveTo(Vec2D(edge.edge.GetP0().GetX() + COLLISION_OFFSET, mAARect.GetTopLeft().GetY()));
	}

}

void Rigidbody::AddForce(const Vec2D& force){
	Vec2D momentumForce = mMass * mVelocity;
	momentumForce += force;
	mVelocity = momentumForce / mMass;
}

void Rigidbody::AddGravityForce(const float gravity){
	if(mUseGravity){
		Vec2D oldVel = mVelocity;
		Vec2D momentumForce = mMass * mVelocity;
		momentumForce += gravity * mGravityScale * mMass * Vec2D(0, 1);
		mVelocity = momentumForce / mMass;
	}
}

void Rigidbody::SetHorizontalVelocity(float velocity){
	mVelocity.SetX(velocity);
}

void Rigidbody::StopOnObstacle(const Vec2D obstacleNormal){
	if(obstacleNormal==DIR_UP && mVelocity.GetY() > 0)
	{
		mVelocity.SetY(0);
	}
	else if(obstacleNormal==DIR_DOWN && mVelocity.GetY() < 0)
	{
		mVelocity.SetY(0);
	}
	else if(obstacleNormal==DIR_LEFT && mVelocity.GetX() > 0)
	{
		mVelocity.SetX(0);
	}
	else if(obstacleNormal==DIR_RIGHT && mVelocity.GetX() < 0)
	{
		mVelocity.SetX(0);
	}
}

bool Rigidbody::CastOrtoRay(const Vec2D& origin, const Vec2D& direction, int lengthLimit){
	int empty;
	return CastOrtoRay(origin, direction, lengthLimit, empty);
}

bool Rigidbody::CastOrtoRay(const Vec2D& origin, const Vec2D& direction, int lengthLimit, int& outID){

	if(direction == Vec2D::Zero){
		return false;
	}

	Vec2D endPoint(Vec2D(origin.GetX()+direction.GetX(), origin.GetY()+direction.GetY()));

	auto UpRayHit = [&](Rigidbody* other){
		if(origin.GetY() > other->mAARect.GetTopLeft().GetY()
			&& endPoint.GetY() < other->mAARect.GetBottomRight().GetY()){
			outID = other->mID;
			return true;
		}
		return false;
	};
	auto DownRayHit = [&](Rigidbody* other){
		if(origin.GetY() < other->mAARect.GetBottomRight().GetY()
			&& endPoint.GetY() > other->mAARect.GetTopLeft().GetY()){
			outID = other->mID;
			return true;
		}
		return false;
	};
	auto RightRayHit = [&](Rigidbody* other){
		if(origin.GetX() < other->mAARect.GetBottomRight().GetX()
			&& endPoint.GetX() > other->mAARect.GetTopLeft().GetX()){
			outID = other->mID;
			return true;
		}
		return false;
	};
	auto LeftRayHit = [&](Rigidbody* other){
		if(origin.GetX() > other->mAARect.GetTopLeft().GetX()
			&& endPoint.GetX() < other->mAARect.GetBottomRight().GetX()){
			outID = other->mID;
			return true;
		}
		return false;
	};

	// Loop through rigidbody world
	for(Rigidbody* otherRigidbody : PhysicsWorld::Singleton().GetAllRigidbodyObjects()){
		if(otherRigidbody->IsCollider() && otherRigidbody->mID != mID){

			// VERTICAL RAY
			if(direction.GetX() == 0
				&& origin.GetX() < otherRigidbody->mAARect.GetBottomRight().GetX()
				&& origin.GetX() > otherRigidbody->mAARect.GetTopLeft().GetX()){

				if(direction.GetY() < 0){
					if(UpRayHit(otherRigidbody))
						return true;
				}else{
					if(DownRayHit(otherRigidbody))
						return true;
				}
			}

			// HORIZONTAL RAY
			if(direction.GetY() == 0
				&& origin.GetY() > otherRigidbody->mAARect.GetTopLeft().GetY()
				&& origin.GetY() < otherRigidbody->mAARect.GetBottomRight().GetY()){

				if(direction.GetX() > 0){
					if(RightRayHit(otherRigidbody))
						return true;
				}else{
					if(LeftRayHit(otherRigidbody))
						return true;
				}
			}
		}
	}
	// If there were no collisions in for loop -> return false
	return false;
}




















