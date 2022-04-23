#include "PhysicsWorld.h"
#include "Rigidbody.h"
#include <vector>
#include <algorithm>
#include <iostream>

PhysicsWorld::PhysicsWorld(){
}

PhysicsWorld& PhysicsWorld::Singleton(){
	static PhysicsWorld world;
	return world;
}

void PhysicsWorld::Update(uint32_t deltaTime){
	// Add gravity force to all Kinematic objects
	for(auto kRB : mKinematicRB){
		kRB->AddGravityForce(GLOBAL_GRAVITY);
		kRB->UpdateRigdbody(deltaTime);
	}
}

std::vector<Rigidbody*> PhysicsWorld::GetAllRigidbodyObjects(){
	auto result = mStaticRB;
	result.insert(result.end(), mKinematicRB.begin(), mKinematicRB.end());
	return result;
}

void PhysicsWorld::RemoveStaticRigidbody(const Rigidbody* removeRB)
{
	 mStaticRB.erase(std::remove(mStaticRB.begin(), mStaticRB.end(), removeRB), mStaticRB.end());
}

void PhysicsWorld::RemoveKinematicRigidbody(const Rigidbody* removeRB)
{
	mKinematicRB.erase(std::remove(mKinematicRB.begin(), mKinematicRB.end(), removeRB), mKinematicRB.end());
}
