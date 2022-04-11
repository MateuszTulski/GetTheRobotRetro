#ifndef SRC_GAMEOBJECTS_PLATFORM_H_
#define SRC_GAMEOBJECTS_PLATFORM_H_

#include "Rigidbody.h"
#include "IGameObject.h"
#include "Line2D.h"
#include "SpriteSheet.h"
#include <memory>

class ColorManipulation;

class Platform : public Rigidbody{

public:
	Platform();
	Platform(const Line2D& line, std::shared_ptr<SpriteSheet> sprite);

	Platform(const Platform& other);

	~Platform() override;

	void Draw(Screen& screen);

private:
	Line2D mLine;
	unsigned int mSegments;
	std::shared_ptr<SpriteSheet> mnoptrSprite;
	ColorManipulation mColorManipulator;
};



#endif /* SRC_GAMEOBJECTS_PLATFORM_H_ */
