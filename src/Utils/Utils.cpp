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
	return (row * imgWidth) + col;
}

float Clamp(float val, float min, float max)
{
	if(val < min){
		val = min;
	}
	if(val > max){
		val = max;
	}
	return val;
}

int Clamp(int val, int min, int max)
{
	if(val < min){
		val = min;
	}
	if(val > max){
		val = max;
	}
	return val;
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
