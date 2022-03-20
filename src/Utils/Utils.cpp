#include "Utils.h"
#include <cmath>

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
