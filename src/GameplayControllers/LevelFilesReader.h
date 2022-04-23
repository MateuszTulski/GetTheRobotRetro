#ifndef SRC_GAMEPLAYCONTROLLERS_LEVELFILESREADER_H_
#define SRC_GAMEPLAYCONTROLLERS_LEVELFILESREADER_H_

#include <fstream>
#include <vector>
#include <memory>
#include "Vec2D.h"
#include "Line2D.h"

enum LevelObjectType{
	LOT_Points = 0,
	LOT_Lines
};

class LevelFilesReader
{
public:
	~LevelFilesReader(){};

	bool LoadFile(const std::string& name, LevelObjectType type, const char& symbol);

	std::unique_ptr<std::vector<Line2D>> GetLines() const;
	std::unique_ptr<std::vector<Vec2D>> GetPoints() const;

private:
	std::vector<Vec2D> mPoints;
	std::vector<Line2D> mLines;
};


#endif /* SRC_GAMEPLAYCONTROLLERS_LEVELFILESREADER_H_ */
