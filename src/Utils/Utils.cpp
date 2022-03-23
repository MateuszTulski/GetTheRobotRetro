#include "Utils.h"
#include <cmath>
#include <cstring>

bool IsEqual(float x, float y){
	return (std::abs((x-y)) < EPSILON);
}

bool IsGreaterThanOrEqual(float x, float y){
	if(IsEqual(x, y)){ return true; }
	return (x>y);
}

bool IsLessThanOrEqual(float x, float y){
	if(IsEqual(x, y)){ return true; }
	return (x<y);
}

float MilisecondsToSeconds(unsigned int miliseconds){
	return static_cast<float>(miliseconds) / 1000.0f;
}

int GetPixelIndex(unsigned int col, unsigned int row, unsigned int imgWidth)
{
	return row * imgWidth + col;
}

std::string StringToUpper(const std::string& inputString)
{
	std::string upper = "";
	for(auto c : inputString)
	{
		upper.push_back(toupper(c));
	}
	return upper;
}
