#ifndef SRC_GAMEOBJECTS_COIN_H_
#define SRC_GAMEOBJECTS_COIN_H_

#include "Rigidbody.h"
#include "Utils.h"

class Coin : public Rigidbody{
public:
	Coin();
	Coin(const Vec2D& position);

	void Draw(Screen& screen, BMPImage& image);

	void SetPosition(const Vec2D& position);
	void OnCollision() override;
private:
	bool isActive;
	const Vec2D SIZE = Vec2D(15, 15);
};


#endif /* SRC_GAMEOBJECTS_COIN_H_ */
