#ifndef SRC_GAMEOBJECTS_OBSTACLE_H_
#define SRC_GAMEOBJECTS_OBSTACLE_H_

#include "Rigidbody.h"
#include "Animation.h"

class Obstacle : public Rigidbody{
public:
	Obstacle();
	Obstacle(const Vec2D& position);
	Obstacle(const Vec2D& position, const float& size);

	Obstacle(const Obstacle& other);

	bool LoadAnimation(const std::string name);

	void Update();
	void Draw(Screen& screen);

	void SetPosition(const Vec2D& position);

	int GetDamage();
	inline void SetDamage(const int& newDamage){damage = newDamage;}
	inline void SetActive(bool active) {isActive = active;}

private:
	bool isDanger;
	bool isActive;
	int damage;

	float disarmedTimer;

	Animation mAnimation;

	void UpdateDisarmedTimer();

	const int DEFAULT_DAMAGE = 3;
	const float DEFAULT_SIZE = 24;
	const float DISARM_AFTER_HIT_TIME = 0.6f;
};



#endif /* SRC_GAMEOBJECTS_OBSTACLE_H_ */
