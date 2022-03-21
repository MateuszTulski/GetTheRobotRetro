#include "Rigidbody.h"
#include "PhysicsWorld.h"
#include "Utils.h"

Rigidbody::Rigidbody() : mVelocity(Vec2D::Zero), mUseGravity(true), mIsCollider(true), mMass(0){
}

Rigidbody::Rigidbody(AARectangle rect, float mass, bool useGravity, bool isCollider) : mVelocity(Vec2D::Zero), mUseGravity(useGravity), mIsCollider(isCollider), mMass(mass){
	Excluder::Init(rect);
}

void Rigidbody::Init(AARectangle rect, float mass, bool useGravity, bool isCollider){
	mUseGravity = useGravity;
	mIsCollider = isCollider;
	mMass = mass;
	Excluder::Init(rect);
}

void Rigidbody::Update(uint32_t deltaTime){
	// Move rigidbody  based on last frame velocity
	Vec2D offset = mVelocity * MilisecondsToSeconds(deltaTime);

	// Check if this move is even possible
	AARectangle offsetRect(mAARect);
	offsetRect.MoveBy(offset);		// Temporary rect to check for the collisions after adding offset

	BoundaryEdge collisionEdge;		// Save collision edge if there is a collision

	// Look for collisions before and after moveing object
	for(auto colliders : PhysicsWorld::Singleton().GetAllRigidbodyObjects()){
		if(colliders.IsCollider()){
			if(HasCollided(colliders.GetAARectangle(), collisionEdge)){
				MakeFlushWithEdge(collisionEdge);
				StopOnObstacle(collisionEdge.normal);
				return;
			}
			if(HasCollided(offsetRect, collisionEdge)){
				return;
			}
		}
	}
	// If there are no collisions, move the object
	MoveBy(offset);
}

void Rigidbody::MakeFlushWithEdge(const BoundaryEdge& edge){

	if(edge.normal == DIR_UP)
	{
		MoveTo(Vec2D(mAARect.GetTopLeft().GetX(), edge.edge.GetP0().GetY() - mAARect.GetHeight()));
	}
	else if(edge.normal == DIR_DOWN)
	{
		MoveTo(Vec2D(mAARect.GetTopLeft().GetX(), edge.edge.GetP0().GetY() + 1));
	}
	else if(edge.normal == DIR_LEFT)
	{
		MoveTo(Vec2D(edge.edge.GetP0().GetX() - mAARect.GetWidth() - 1, mAARect.GetTopLeft().GetY()));
	}
	else if(edge.normal == DIR_RIGHT)
	{
		MoveTo(Vec2D(edge.edge.GetP0().GetX() + 1, mAARect.GetTopLeft().GetY()));
	}

}

void Rigidbody::AddForce(const Vec2D& force){
	Vec2D momentumForce = mMass * mVelocity;
	momentumForce += force;
	mVelocity = momentumForce / mMass;
}

void Rigidbody::AddGravityForce(const float gravity){
	if(mUseGravity){
		Vec2D momentumForce = mMass * mVelocity;
		momentumForce += gravity * mMass * Vec2D(0, -1);
		mVelocity = momentumForce / mMass;
	}
}

void Rigidbody::SetHorizontalVelocity(float velocity){
	mVelocity.SetX(velocity);
}

void Rigidbody::StopOnObstacle(const Vec2D normal){
	if(normal==DIR_UP && mVelocity.GetY() < 0)
	{
		mVelocity.SetY(0);
	}
	else if(normal==DIR_DOWN && mVelocity.GetY() > 0)
	{
		mVelocity.SetY(0);
	}
	else if(normal==DIR_LEFT && mVelocity.GetX() < 0)
	{
		mVelocity.SetX(0);
	}
	else if(normal==DIR_RIGHT && mVelocity.GetX() > 0)
	{
		mVelocity.SetX(0);
	}
}


