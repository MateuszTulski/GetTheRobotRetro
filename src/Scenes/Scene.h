#ifndef SCENES_SCENE_H_
#define SCENES_SCENE_H_

#include <stdint.h>
#include <string>
#include "GameController.h"

class Screen;

// Interface
class Scene{
public:
	virtual ~Scene(){};
	virtual void Init() = 0;
	virtual void Update(uint32_t deltaTime) = 0;
	virtual void Draw(Screen& screen) = 0;
	virtual const std::string& GetSceneName() const = 0;

	GameController* GetGameController() {return &mGameController;}

protected:
	GameController mGameController;
};


#endif /* SCENES_SCENE_H_ */
