#include <algorithm>
#include <iostream>

#include "PhysicsWorld.h"
#include "Rigidbody.h"
#include "GlobalSettings.h"

int PhysicsWorld::NumberOfLayers {0};

PhysicsWorld::PhysicsWorld(){
	mPhysicsLayers.emplace("default", 0);
}

PhysicsWorld& PhysicsWorld::Singleton(){
	static PhysicsWorld world;
	return world;
}

void PhysicsWorld::Update(uint32_t deltaTime){
	// Add gravity force to all Kinematic objects
	for(auto kRB : mKinematicRB){
		kRB->AddGravityForce(GLOBAL_GRAVITY * GRAVITY_SCALE);
		kRB->UpdateCollisions(deltaTime);
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

bool PhysicsWorld::GetPhysicsLayer(const std::string& name, int& outId){
	for(auto it = mPhysicsLayers.begin(); it != mPhysicsLayers.end(); it++){
		if(it->first == name){
			outId = it->second;
			return true;
		}
	}
	return false;
}

void PhysicsWorld::AddPhysicsLayer(const std::string& name, int& outId){
	++NumberOfLayers;
	mPhysicsLayers.emplace(name, NumberOfLayers);
	outId = NumberOfLayers;
}

std::string PhysicsWorld::GetPhysicsLayerName(const int& id) const {
	for(auto it = mPhysicsLayers.begin(); it != mPhysicsLayers.end(); it++){
		if(it->second == id){
			return it->first;
		}
	}
	return "default";
}
