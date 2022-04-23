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
	Vec2D finalOffset = mVelocity * MilisecondsToSeconds(deltaTime);

	BoundaryEdge outEdge;		// Edge on the collided obstacle

	// Look for collisions before and after moving object
	for(Rigidbody* otherRigidbody : PhysicsWorld::Singleton().GetAllRigidbodyObjects()){
		if(otherRigidbody->IsCollider() && mID != otherRigidbody->GetRigidbodyID())
		{
			// Check if rigidbody is already colliding
			if(HasCollided(*otherRigidbody, outEdge))
			{
				MakeFlushWithEdge(outEdge);

				StopOnObstacle(outEdge.normal);

				if(!IsEqual(outEdge.normal.GetX(), 0))
				{
					finalOffset.SetX(0);
				}
				if(!IsEqual(outEdge.normal.GetY(), 0))
				{
					finalOffset.SetY(0);
				}
			}
			
//			 Check possible collision after finalOffset
			Excluder offsetGhost;
			offsetGhost.Init(GetAARectangle());
			offsetGhost.MoveBy(finalOffset);

			if(offsetGhost.HasCollided(*otherRigidbody, outEdge))
			{
				// Movement will cause a collision, so don't do it
				MakeFlushWithEdge(outEdge);
				StopOnObstacle(outEdge.normal);

				if(!IsEqual(outEdge.normal.GetX(), 0))
				{
					finalOffset.SetX(0);
				}
				if(!IsEqual(outEdge.normal.GetY(), 0))
				{
					finalOffset.SetY(0);
				}
			}
		}
	}

	MoveBy(finalOffset);
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


