#include "LevelFilesReader.h"
#include "Color.h"
#include "App.h"
#include <stdint.h>
#include <fstream>

bool LevelFilesReader::LoadFile(const std::string& name, LevelObjectType type, const char& symbol)
{
	std::string path = App::Singleton().GetBasePath() + "Assets/Level001/" + name;

	std::ifstream file(path);
	if(!file.is_open())
	{
		std::cout << "Error while opening the file: " << path << std::endl;
		return false;
	}

	std::string line;
	unsigned int row{0};
	unsigned int col{0};

	if(type == LOT_Points)
	{
		while(getline(file, line))
		{
			row ++;
			for(char c : line)
			{
				col ++;
				if(c == symbol){

					mPoints.push_back(Vec2D(col, row));
				}
			}
			col = 0;	// Reset column number
		}
	}
	else if (type == LOT_Lines)
	{
		Vec2D p0, p1;
		int points{0};
		char lastSymbol;

		while(getline(file, line))
		{
			row ++;
			for(char c : line)
			{
				col ++;

				if(c == symbol && points == 0){
					p0 = Vec2D(col, row);
					points ++;
				}
				if(c == symbol && points == 1){
					lastSymbol = c;
				}
				if(c != symbol && points == 1){
					p1 = Vec2D(col-1, row);
					mLines.push_back(Line2D(p0, p1));
					points = 0;
				}

			}
			col = 0;	// Reset column number
		}
	}

	return true;
}

std::unique_ptr<std::vector<Line2D>> LevelFilesReader::GetLines() const
{

	std::unique_ptr<std::vector<Line2D>> lines = std::make_unique<std::vector<Line2D>>(mLines);
	return lines;
}

std::unique_ptr<std::vector<Vec2D>> LevelFilesReader::GetPoints() const
{
	std::unique_ptr<std::vector<Vec2D>> points = std::make_unique<std::vector<Vec2D>>(mPoints);
	return points;
}
