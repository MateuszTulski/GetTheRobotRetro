#ifndef SRC_GAMEOBJECTS_COIN_H_
#define SRC_GAMEOBJECTS_COIN_H_

#include "Rigidbody.h"
#include "Utils.h"

class Coin : public Rigidbody{
public:
	Coin();
	Coin(const Vec2D& position);

	Coin(const Coin& other);

	void Draw(Screen& screen, BMPImage& image) const;
	void SetPosition(const Vec2D& position);

	void SetActive(bool active);

	inline int CollectCoin() {return COIN_VALUE;}
	inline bool IsActive() const {return isActive;}

private:
	bool isActive;
	const int COIN_VALUE = 5;
	const Vec2D SIZE = Vec2D(15, 15);
};


#endif /* SRC_GAMEOBJECTS_COIN_H_ */
