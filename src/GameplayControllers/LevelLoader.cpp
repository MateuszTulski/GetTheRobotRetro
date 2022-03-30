#include "LevelLoader.h"
#include "LevelFilesReader.h"
#include "Platform.h"

bool LevelLoader::LoadGraphics()
{
	SpriteSheet platforms;
	if(platforms.LoadSprite("platform"))
	{
		// Save pointer
		moptrPlatformSprite = std::make_shared<SpriteSheet>(platforms);
	}else{
		return false;
	}


	return true;
}

bool LevelLoader::LoadPlatforms()
{
	LevelFilesReader lines;
	std::string fileName("platforms");
	if(lines.LoadFile(fileName, LOT_Lines, 'x'))
	{
		mPlatformsLines = lines.GetLines();

		for(auto p : *mPlatformsLines)
		{
			Platform platform(p, moptrPlatformSprite);
			Vec2D leftTop((p.GetP0().GetX()-1) * 40, (p.GetP0().GetY()-1) * 40);
			Vec2D rightBottom(p.GetP1().GetX() * 40, p.GetP1().GetY() * 40);
			platform.Init(AARectangle(leftTop, rightBottom), 10, false, true);
			mPlatforms.push_back(platform);
		}

	}else{
		return false;
	}

	return true;
}

void LevelLoader::DrawObjects(Screen& screen)
{
	for(auto p : mPlatforms)
	{
		p.Draw(screen);
	}
}
