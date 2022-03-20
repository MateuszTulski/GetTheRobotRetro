#ifndef SRC_GAMEOBJECTS_PLAYER_H_
#define SRC_GAMEOBJECTS_PLAYER_H_

#include "AARectangle.h"
#include "Rigidbody.h"

class Screen;
class BoundaryEdge;

class Player {
public:
	void Update(uint32_t deltaTime);
	void Draw(Screen& screen);
	void MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& point, bool limitToEdge);

	void Run();
	void Jump(const BoundaryEdge& edge);
private:
	Rigidbody mRigidbody;
	AARectangle mBoundary;
	const float mRunSpeed = 50.0f;
	const float mMass = 50.0f;
};



#endif /* SRC_GAMEOBJECTS_PLAYER_H_ */
