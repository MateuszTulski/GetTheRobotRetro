#include "LevelLoader.h"
#include "LevelFilesReader.h"
#include "Platform.h"

bool LevelLoader::LoadGraphics()
{
	SpriteSheet platforms;
	if(platforms.LoadSprite("platform"))
	{
		moptrPlatformSprite = std::make_shared<SpriteSheet>(platforms);
	}
	else
	{
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
		mPlatforms.reserve(mPlatformsLines->size());

		for(auto p : *mPlatformsLines)
		{
			mPlatforms.emplace_back(Platform(p, moptrPlatformSprite));

			Vec2D leftTop((p.GetP0().GetX()-1) * LevelLoader::LEVEL_GRID_SIZE, (p.GetP0().GetY()-1) * LevelLoader::LEVEL_GRID_SIZE);
			Vec2D rightBottom(p.GetP1().GetX() * LevelLoader::LEVEL_GRID_SIZE, p.GetP1().GetY() * LevelLoader::LEVEL_GRID_SIZE);

			mPlatforms.back().InitRigidbody(AARectangle(leftTop, rightBottom), 10, false, true);
		}

	}else{
		return false;
	}

	return true;
}

void LevelLoader::DrawObjects(Screen& screen){
	float rightScreenSide = screen.GetScreenRect().GetBottomRight().GetX();
	float leftScreenSide = screen.GetScreenRect().GetTopLeft().GetX();

	DrawPlatforms(screen, rightScreenSide, leftScreenSide);
	DrawCoins(screen, rightScreenSide, leftScreenSide);
	DrawObstacles(screen, rightScreenSide, leftScreenSide);
}

void LevelLoader::DrawPlatforms(Screen& screen, float rightScreenSide, float leftScreenSide){
	for(auto& p : mPlatforms){
		if(p.GetAARectangle().GetTopLeft().GetX() > rightScreenSide || p.GetAARectangle().GetBottomRight().GetX() < leftScreenSide ){
			continue;
		}
		p.Draw(screen);
	}
}

void LevelLoader::DrawCoins(Screen& screen, float rightScreenSide, float leftScreenSide){

}

void LevelLoader::DrawObstacles(Screen& screen, float rightScreenSide, float leftScreenSide){

}

