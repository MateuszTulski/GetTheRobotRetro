#include "PhysicsWorld.h"
#include "Rigidbody.h"
#include <vector>
#include <iostream>

PhysicsWorld::PhysicsWorld(){
}

PhysicsWorld& PhysicsWorld::Singleton(){
	static PhysicsWorld world;
	return world;
}

void PhysicsWorld::Update(uint32_t deltaTime){
	// Add gravity force to all kinematic objects
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
