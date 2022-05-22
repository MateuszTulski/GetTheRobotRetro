#include "App.h"
#include "LevelLoader.h"
#include "LevelFilesReader.h"
#include "Platform.h"

bool LevelLoader::LoadGraphics(){
	auto loadPlatforms = [this](){
		SpriteSheet platforms;
		if(platforms.LoadSprite("platform")){
			moptrPlatformSprite = std::make_shared<SpriteSheet>(platforms);
			return true;
		}
		return false;
	};

	auto loadCoins = [this](){
		return coinsImage.LoadImage(App::Singleton().GetBasePath() + "Assets/coin.bmp");
	};

	return loadPlatforms() && loadCoins();
}

bool LevelLoader::LoadLevelObjects(){
	return LoadPlatforms() && LoadCoins();
}

bool LevelLoader::LoadPlatforms(){
	LevelFilesReader lines;
	std::string fileName("level");
	if(lines.LoadFile(fileName, LOT_Lines, 'x')){
		std::vector<Line2D> mPlatformsLines = lines.GetLines();
		mPlatforms.reserve(mPlatformsLines.size());

		for(auto p : mPlatformsLines){
			mPlatforms.emplace_back(Platform(p, moptrPlatformSprite));

			Vec2D leftTop((p.GetP0().GetX()-1) * LevelLoader::LEVEL_GRID_SIZE, (p.GetP0().GetY()-1) * LevelLoader::LEVEL_GRID_SIZE);
			Vec2D rightBottom(p.GetP1().GetX() * LevelLoader::LEVEL_GRID_SIZE, p.GetP1().GetY() * LevelLoader::LEVEL_GRID_SIZE);

			mPlatforms.back().InitRigidbody(AARectangle(leftTop, rightBottom), 10, false, true);
		}
		return true;
	}else{
		return false;
	}
}

bool LevelLoader::LoadCoins(){
	LevelFilesReader coinsPoints;
	std::string fileName("level");
	if(coinsPoints.LoadFile(fileName, LOT_Points, 'c')){
		std::vector<Vec2D> points = coinsPoints.GetPoints();
		mCoins.reserve(points.size());
		if(points.size() > 0){
			for(auto p : points){
				Vec2D position(Vec2D(p.GetX()*LEVEL_GRID_SIZE, (p.GetY()-1)*LEVEL_GRID_SIZE));
				mCoins.emplace_back(position);
				mCoins.back().SetPhysicsLayer("coins");
				mCoins.back().SetAsTrigger(true);
			}
		}
		return true;
	}else{
		return false;
	}
}

void LevelLoader::DrawObjects(Screen& screen){
	float rightScreenSide = screen.GetScreenRect().GetBottomRight().GetX();
	float leftScreenSide = screen.GetScreenRect().GetTopLeft().GetX();

	DrawPlatforms(screen, rightScreenSide, leftScreenSide);
	DrawCoins(screen, rightScreenSide, leftScreenSide);
	DrawObstacles(screen, rightScreenSide, leftScreenSide);
}

void LevelLoader::Restart(){
	for(auto& c : mCoins){
		c.SetActive(true);
	}
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
	for(const auto& c : mCoins){
		c.Draw(screen, coinsImage);
	}
}

void LevelLoader::DrawObstacles(Screen& screen, float rightScreenSide, float leftScreenSide){

}

