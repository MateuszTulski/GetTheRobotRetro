#ifndef SRC_GAMEOBJECTS_PLAYER_H_
#define SRC_GAMEOBJECTS_PLAYER_H_

#include "AARectangle.h"
#include "Rigidbody.h"

class Screen;
class BoundaryEdge;

class Player : public Rigidbody {
public:
	Player();
	void Update(uint32_t deltaTime);
	void Draw(Screen& screen);
	void MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& point, bool limitToEdge);

	void Run();
	void Jump(const BoundaryEdge& edge);
private:
	const float RUN_SPEED = 50.0f;
	const float MASS = 50.0f;
	const float WIDTH = 24;
	const float HEIGHT = 56;
	const AARectangle PLAYER_RECT = {Vec2D::Zero, WIDTH, HEIGHT};
};



#endif /* SRC_GAMEOBJECTS_PLAYER_H_ */
