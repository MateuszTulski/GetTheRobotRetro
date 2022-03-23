#include <fstream>
#include <sstream>
#include "SpriteSheet.h"
#include "App.h"
#include "BMPImage.h"

SpriteSheet::SpriteSheet(){
}

bool SpriteSheet::LoadSprite(const std::string& name)
{
	bool imageLoaded = mImage.LoadImage(App::Singleton().GetBasePath() + std::string("Assets/") + name + ".bmp");
	bool spriteSectionsLoaded = LoadSpriteSections(App::Singleton().GetBasePath() + std::string("Assets/") + name + ".txt");

	return imageLoaded && spriteSectionsLoaded;
}

Sprite SpriteSheet::GetSprite(const std::string& name) const
{
	std::string key = StringToUpper(name);
	Sprite empty;

	for(const auto& el : mSpriteSections)
	{
		if(el.key == key)
		{
			return el.sprite;
		}
	}
	return empty;
}

std::vector<std::string> SpriteSheet::GetSpritestNames() const
{
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
		std::cout << "Couldn't open font sections file!" << std::endl;
		return false;
	}

	std::string line;

	while(std::getline(fs, line))
	{
		std::string command;
		std::stringstream ss;
		ss << line;

		while(ss >> command)
		{
			if(command == ":key")
			{
				mReadField = [&](std::string command){
					SpriteSection newSection;
					newSection.key = command;
					mSpriteSections.push_back(newSection);
				};
			}
			else if(command == ":xPos")
			{
				mReadField = [&](std::string command){
					mSpriteSections.back().sprite.xPos = std::stoi(command);
				};
			}
			else if(command == ":yPos")
			{
				mReadField = [&](std::string command){
					mSpriteSections.back().sprite.yPos = std::stoi(command);
				};
			}
			else if(command == ":width")
			{
				mReadField = [&](std::string command){
					mSpriteSections.back().sprite.width = std::stoi(command);
				};
			}
			else if(command == ":height")
			{
				mReadField = [&](std::string command){
					mSpriteSections.back().sprite.height = std::stoi(command);
				};
			}
			else
			{
				// Read the property
				mReadField(command);
			}
		}

	}
	return true;
}


