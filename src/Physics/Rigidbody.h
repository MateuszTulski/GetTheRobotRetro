#ifndef SRC_PHYSICS_RIGIDBODY_H_
#define SRC_PHYSICS_RIGIDBODY_H_

#include <stdint.h>
#include "AARectangle.h"
#include "Vec2D.h"

class Rigidbody{
public:
	Rigidbody();
	void Init(const AARectangle& rect, const float& mass, bool isKinematic);
	void Update(uint32_t deltaTime, const Vec2D position);
	Vec2D GetPhysicsMoveResult(const Vec2D offset) const;

	void AddForce(const Vec2D& force);
	void SetVelocity(const Vec2D& velocity);
	inline Vec2D GetVelocity() const {return mVelocity;}
	void Stop();


private:
	AARectangle mAARect;
	Vec2D mVelocity;
	float mMass;
	bool mIsKinematic;
};


#endif /* SRC_PHYSICS_RIGIDBODY_H_ */
