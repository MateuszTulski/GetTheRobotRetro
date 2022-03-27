#ifndef SRC_PHYSICS_RIGIDBODY_H_
#define SRC_PHYSICS_RIGIDBODY_H_

#include <stdint.h>
#include "AARectangle.h"
#include "Excluder.h"
#include "Vec2D.h"
#include "Screen.h"

class Rigidbody : public Excluder{
public:
	Rigidbody();
	Rigidbody(AARectangle rect, float mass, bool useGravity = true, bool isCollider = true);
	~Rigidbody();

	//// TEMP
	inline void Draw(Screen& screen){ screen.Draw(mAARect, Color::Red(), true, Color::Red());}

	bool operator==(const Rigidbody& other);

	void Init(AARectangle rect, float mass, bool useGravity = true, bool isCollider = true);
	void UpdateRigdbody(uint32_t deltaTime);

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

	inline void SetGravityScale(const float& gravityScale) { mGravityScale = gravityScale;}

	inline int GetRigidbodyID() const {return mID;}

	static int InitializedRigidbody;

private:
	Vec2D mVelocity;
	bool mUseGravity;
	bool mIsCollider;
	float mMass;
	float mGravityScale = 1;
	int mID;
	int test = 0;

	float const COLLISION_OFFSET = 0.5f;
};


#endif /* SRC_PHYSICS_RIGIDBODY_H_ */
