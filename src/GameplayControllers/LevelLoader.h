#ifndef SRC_GAMEPLAYCONTROLLERS_LEVELLOADER_H_
#define SRC_GAMEPLAYCONTROLLERS_LEVELLOADER_H_

#include <memory>
#include "BMPImage.h"
#include "SpriteSheet.h"
#include "Line2D.h"
#include "Platform.h"
#include "Coin.h"

class LevelLoader {

public:
	bool LoadGraphics();
	bool LoadLevelObjects();

	void DrawObjects(Screen& screen);

	static const unsigned int LEVEL_GRID_SIZE = 20;

private:
	std::shared_ptr<SpriteSheet> moptrPlatformSprite;

	BMPImage coinsImage;

	std::vector<Platform> mPlatforms;
	std::vector<Coin> mCoins;

	bool LoadPlatforms();
	bool LoadCoins();

	void DrawPlatforms(Screen& screen, float rightScreenSide, float leftScreenSide);
	void DrawCoins(Screen& screen, float rightScreenSide, float leftScreenSide);
	void DrawObstacles(Screen& screen, float rightScreenSide, float leftScreenSide);
};



#endif /* SRC_GAMEPLAYCONTROLLERS_LEVELLOADER_H_ */
