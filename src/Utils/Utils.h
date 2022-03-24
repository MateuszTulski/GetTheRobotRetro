#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>

static const float EPSILON = 0.0001f;

static const float PI = 3.14159265359;
static const float TWO_PI = 2 * PI;

bool IsEqual(float x, float y);

bool IsGreaterThanOrEqual(float x, float y);

bool IsLessThanOrEqual(float x, float y);

float MilisecondsToSeconds(unsigned int miliseconds);

int GetPixelIndex(unsigned int col, unsigned int row, unsigned int imgWidth);

float Clamp(float val, float min, float max);

std::string StringToUpper(const std::string& inputString);

struct Size{
	unsigned int width = 0, height = 0;
};

#endif
