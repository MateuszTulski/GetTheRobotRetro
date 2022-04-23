#include <fstream>
#include <sstream>
#include <iostream>

#include "SpriteSheet.h"
#include "App.h"

SpriteSheet::SpriteSheet(){
	mScale.xScale = 1;
	mScale.yScale = 1;
}

bool SpriteSheet::LoadSprite(const std::string& name){

	bool imageLoaded = mImage.LoadImage(App::Singleton().GetBasePath() + std::string("Assets/") + name + ".bmp");
	bool spriteSectionsLoaded = LoadSpriteSections(App::Singleton().GetBasePath() + std::string("Assets/") + name + ".txt");

	if(name == "Animations/player-run"){
		auto sections = mSpriteSections;
	}

	return imageLoaded && spriteSectionsLoaded;
}

void SpriteSheet::ScaleSpriteSheet(float xScale, float yScale, bool relative){

	if(relative)
	{
		mScale.xScale *= xScale;
		mScale.yScale *= yScale;
	}
	else
	{
		mScale.xScale = xScale;
		mScale.yScale = yScale;
	}

	mImage.ScaleImage(xScale, yScale, relative);
}

Sprite SpriteSheet::GetSpriteCoordinates(const std::string& name) const{

	std::string key = StringToUpper(name);
	Sprite empty;

	for(const auto& el : mSpriteSections)
	{
		if(StringToUpper(el.key) == key)
		{
			Sprite coordinates = el.sprite;
			coordinates.xPos *= mScale.xScale;
			coordinates.yPos *= mScale.yScale;
			coordinates.width *= mScale.xScale;
			coordinates.height *= mScale.yScale;

			return coordinates;
		}
	}
	return empty;
}

std::vector<std::string> SpriteSheet::GetSpritestNames() const{

	std::vector<std::string> names;
	for(const auto& n : mSpriteSections)
	{
		names.push_back(n.key);
	}
	return names;
}

bool SpriteSheet::LoadSpriteSections(const std::string& path){

	std::ifstream fs;
	fs.open(path);

	if(!fs.is_open()){
		std::cout << "Couldn't open sprite sections file!" << std::endl;
		return false;
	}

	std::string line;

	while(std::getline(fs, line))
	{
		std::string command;
		std::stringstream ss;
		ss << line;

		bool readValueInNextIteration {false};
		while(ss >> command)
		{
			if(command == ":key")
			{
				readValueInNextIteration = true;
				mReadField = [&](std::string command){
					SpriteSection newSection;
					newSection.key = command;
					mSpriteSections.push_back(newSection);
				};
			}
			else if(command == ":xPos")
			{
				readValueInNextIteration = true;
				mReadField = [&](std::string command){
					mSpriteSections.back().sprite.xPos = std::stoi(command);
				};
			}
			else if(command == ":yPos")
			{
				readValueInNextIteration = true;
				mReadField = [&](std::string command){
					mSpriteSections.back().sprite.yPos = std::stoi(command);
				};
			}
			else if(command == ":width")
			{
				readValueInNextIteration = true;
				mReadField = [&](std::string command){
					mSpriteSections.back().sprite.width = std::stoi(command);
				};
			}
			else if(command == ":height")
			{
				readValueInNextIteration = true;
				mReadField = [&](std::string command){
					mSpriteSections.back().sprite.height = std::stoi(command);
				};
			}
			else if(readValueInNextIteration)
			{
				// Read the property
				mReadField(command);
			}
		}

	}
	return true;
}


