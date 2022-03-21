#ifndef SRC_PHYSICS_RIGIDBODY_H_
#define SRC_PHYSICS_RIGIDBODY_H_

#include <stdint.h>
#include "AARectangle.h"
#include "Excluder.h"
#include "Vec2D.h"

class Rigidbody : public Excluder{
public:
	Rigidbody();
	Rigidbody(AARectangle rect, float mass, bool useGravity = true, bool isCollider = true);
	void Init(AARectangle rect, float mass, bool useGravity = true, bool isCollider = true);
	void Update(uint32_t deltaTime);

	void MakeFlushWithEdge(const BoundaryEdge& edge);

	void AddForce(const Vec2D& force);
	void AddGravityForce(const float gravity);
	void SetHorizontalVelocity(float velocity);
	inline Vec2D GetVelocity() const {return mVelocity;}
	void StopOnObstacle(const Vec2D normal);

	inline bool IsCollider() const {return mIsCollider;}
	inline bool IsUseingGravity() const {return mUseGravity;}

	inline void SetCollider(bool on) {mIsCollider = on;}
	inline void SetGravity(bool use) {mUseGravity = use;}

private:
	Vec2D mVelocity;
	bool mUseGravity;
	bool mIsCollider;
	float mMass;
};


#endif /* SRC_PHYSICS_RIGIDBODY_H_ */
