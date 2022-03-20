#ifndef _UTILS_H_
#define _UTILS_H_

static const float EPSILON = 0.0001f;

static const float PI = 3.14159265359;
static const float TWO_PI = 2 * PI;

bool IsEqual(float x, float y);

bool IsGreaterThanOrEqual(float x, float y);

bool IsLessThanOrEqual(float x, float y);

float MilisecondsToSeconds(unsigned int miliseconds);

#endif
