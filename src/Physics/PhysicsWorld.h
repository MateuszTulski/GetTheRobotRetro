#ifndef SRC_PHYSICS_PHYSICSWORLD_H_
#define SRC_PHYSICS_PHYSICSWORLD_H_

#include <vector>
#include <map>
#include <stdint.h>
#include <iostream>
#include <vector>

#include "Rigidbody.h"

class PhysicsWorld{

public:
	PhysicsWorld();
	static PhysicsWorld& Singleton();
	static int NumberOfLayers;

	void Update(uint32_t deltaTime);

	inline void AddStaticRigidbody(Rigidbody* rigidbody) {mStaticRB.push_back(rigidbody);}
	inline void AddKinematicRigidbody(Rigidbody* rigidbody) {mKinematicRB.push_back(rigidbody);}

	void RemoveStaticRigidbody(const Rigidbody* rigidbody);
	void RemoveKinematicRigidbody(const Rigidbody* rigidbody);

	inline std::vector<Rigidbody*> GetStaticRigidbodyObjects() {return mStaticRB;}
	inline std::vector<Rigidbody*> GetKinematicRigidbodyObjects() {return mKinematicRB;}
	std::vector<Rigidbody*> GetAllRigidbodyObjects();

	bool GetPhysicsLayer(const std::string& name, int& outId);
	void AddPhysicsLayer(const std::string& name, int& outId);
	std::string GetPhysicsLayerName(const int& id) const;

	inline float GetGravity() const {return GLOBAL_GRAVITY;}

private:
	std::vector<Rigidbody*> mKinematicRB;
	std::vector<Rigidbody*> mStaticRB;
	std::map<std::string, int> mPhysicsLayers;

	const float GLOBAL_GRAVITY = 10.0f;
};


#endif /* SRC_PHYSICS_PHYSICSWORLD_H_ */
