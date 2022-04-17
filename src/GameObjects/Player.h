#ifndef SRC_GAMEOBJECTS_PLAYER_H_
#define SRC_GAMEOBJECTS_PLAYER_H_

#include "AARectangle.h"
#include "Rigidbody.h"

class Screen;
class BoundaryEdge;

class Player : public Rigidbody {
public:
	Player();

	Player(const Player& other);
	Player(Player&& other);

	void Init(const Vec2D& startPosition);
	void Update(uint32_t deltaTime);
	void Draw(Screen& screen);
	void MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& point, bool limitToEdge);

	void Run(signed int direction, bool released = false);
	void Jump(bool jumpPressed);
	void SetPosition(Vec2D bottomMiddlePoint);

private:
	bool mJumpPressed;

	const float RUN_SPEED = 75.0f;
	const float MASS = 20.0f;
	const float WIDTH = 24;
	const float HEIGHT = 56;
	const float JUMP_FORCE = 13000;

	bool RIGHT_KEY_PRESSED = false;
	bool LEFT_KEY_PRESSED = false;

	const AARectangle PLAYER_RECT = {Vec2D::Zero, WIDTH, HEIGHT};
};



#endif /* SRC_GAMEOBJECTS_PLAYER_H_ */
