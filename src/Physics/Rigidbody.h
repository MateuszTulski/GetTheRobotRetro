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
	Rigidbody(AARectangle rect, float mass, const std::string layer, bool useGravity = true, bool isCollider = true);

	~Rigidbody();

	bool operator==(const Rigidbody& other);

	void InitRigidbody(AARectangle rect, float mass, bool useGravity = true, bool isCollider = true);
	void UpdateCollisions(uint32_t deltaTime);

	void MakeFlushWithEdge(const BoundaryEdge& edge);

	void AddForce(const Vec2D& force);
	void AddGravityForce(const float gravity);

	void SetHorizontalVelocity(float velocity);
	void SetVerticalVelocity(float velocity);

	inline Vec2D GetVelocity() const {return mVelocity;}
	void StopOnObstacle(const Vec2D normal);

	inline bool IsCollider() const {return mIsCollider;}
	inline bool IsUseingGravity() const {return mUseGravity;}
	inline bool IsTrigger() const {return mIsTrigger;}

	inline void SetCollider(bool on) {mIsCollider = on;}
	inline void SetGravity(bool use) {mUseGravity = use;}
	inline void SetAsTrigger(bool trigger) {mIsTrigger = trigger;}

	inline void SetGravityScale(const float& gravityScale) { mGravityScale = gravityScale;}

	inline int GetRigidbodyID() const {return mID;}
	inline AARectangle GetAARectangle() const {return mAARect;}

	void SetPhysicsLayer(const std::string& name);
	std::string GetPhysicsLayerName() const;
	bool IsOnLayer(const std::string& name);

	bool CastOrtoRay(const Vec2D& origin, const Vec2D& direction, int lengthLimit);
	bool CastOrtoRay(const Vec2D& origin, const Vec2D& direction, int lengthLimit, int& outID);

	virtual void OnCollision(Rigidbody& outCollider){}

	static int InitializedRigidbody;

private:
	Vec2D mVelocity;
	bool mUseGravity;
	bool mIsCollider;
	bool mIsTrigger;
	float mMass;
	float mGravityScale = 1;
	int mID;
	int mLayerId;

	float const COLLISION_OFFSET = 1.2f;

	void ResetOffsetOnObstacle(Vec2D& offset, const BoundaryEdge& obstacleEdge);
};


#endif /* SRC_PHYSICS_RIGIDBODY_H_ */
