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

	inline std::vector<Line2D> GetLines() const {return mLines;}
	inline std::vector<Vec2D> GetPoints() const {return mPoints;}

private:
	std::vector<Vec2D> mPoints;
	std::vector<Line2D> mLines;
};


#endif /* SRC_GAMEPLAYCONTROLLERS_LEVELFILESREADER_H_ */
