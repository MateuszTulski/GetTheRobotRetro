#include "Rigidbody.h"
#include "PhysicsWorld.h"
#include "Utils.h"
#include <iostream>

int Rigidbody::InitializedRigidbody = 0;

Rigidbody::Rigidbody() : Rigidbody(AARectangle(Vec2D::Zero, Vec2D::Zero), 0, true, true){
}

Rigidbody::Rigidbody(AARectangle rect, float mass, bool useGravity, bool isCollider) : mVelocity(Vec2D::Zero), mUseGravity(useGravity), mIsCollider(isCollider), mMass(mass){
	InitializedRigidbody++;
	mID = InitializedRigidbody;
	Excluder::Init(rect);
}

Rigidbody::~Rigidbody(){
	if(mUseGravity){
		PhysicsWorld::Singleton().RemoveKinematicRigidbody(this);
	}else{
		PhysicsWorld::Singleton().RemoveStaticRigidbody(this);
	}

//	PhysicsWorld::Singleton().
}

bool Rigidbody::operator==(const Rigidbody& other){
	return this->mID == other.GetRigidbodyID();
}

void Rigidbody::Init(AARectangle rect, float mass, bool useGravity, bool isCollider){
	mUseGravity = useGravity;
	mIsCollider = isCollider;
	mMass = mass;
	Excluder::Init(rect);
	// Add this rigigbody to the world
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
	// Move rigidbody  based on last frame velocity
	Vec2D offset = mVelocity * MilisecondsToSeconds(deltaTime);

	BoundaryEdge collisionEdge;		// Save collision edge if there is a collision

	// Look for collisions before and after moveing object
	for(auto collider : PhysicsWorld::Singleton().GetAllRigidbodyObjects()){
		if(collider->IsCollider() && mID != collider->GetRigidbodyID()){
			if(HasCollided(collider->GetAARectangle(), collisionEdge)){
				MakeFlushWithEdge(collisionEdge);
				StopOnObstacle(collisionEdge.normal);
				return;
			}
			// Check collision after offset
			Excluder offsetRect;
			offsetRect.Init(GetAARectangle());
			offsetRect.MoveBy(offset);
			if(offsetRect.HasCollided(collider->GetAARectangle(), collisionEdge)){
				// Movement will cause a collision! Return
				StopOnObstacle(collisionEdge.normal);
				if(!IsEqual(collisionEdge.normal.GetX(), 0))
				{
					offset.SetX(0);
				}
				if(!IsEqual(collisionEdge.normal.GetY(), 0)){
					offset.SetY(0);
				}
			}
		}
	}
	MoveBy(offset);
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


