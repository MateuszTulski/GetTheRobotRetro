#ifndef SRC_GAMEOBJECTS_IGAMEOBJECT_H_
#define SRC_GAMEOBJECTS_IGAMEOBJECT_H_

#include <stdint.h>

class Screen;

class IGameObject{
public:
	virtual ~IGameObject();

	virtual void Draw(Screen& screen) = 0;
	virtual void Update(uint32_t deltaTime) = 0;
};


#endif /* SRC_GAMEOBJECTS_IGAMEOBJECT_H_ */
