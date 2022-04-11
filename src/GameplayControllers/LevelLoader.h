#ifndef SRC_GAMEPLAYCONTROLLERS_LEVELLOADER_H_
#define SRC_GAMEPLAYCONTROLLERS_LEVELLOADER_H_

#include <memory>
#include "SpriteSheet.h"
#include "Line2D.h"
#include "IGameObject.h"
#include "Platform.h"

class LevelLoader {

public:
	bool LoadGraphics();
	bool LoadPlatforms();

	void DrawObjects(Screen& screen);

	static const unsigned int LEVEL_GRID_SIZE = 20;

private:
	std::unique_ptr<std::vector<Line2D>> mPlatformsLines;
	std::shared_ptr<SpriteSheet> moptrPlatformSprite;

	std::vector<Platform> mPlatforms;

};



#endif /* SRC_GAMEPLAYCONTROLLERS_LEVELLOADER_H_ */
