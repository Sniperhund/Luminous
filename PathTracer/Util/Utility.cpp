#include "Utility.h"

#include <corecrt_math_defines.h>
#include <cstdlib>

int Utility::SamplesPerPixel = 1024;
int Utility::MaxDepth = 4;

float Utility::Epsilon = std::numeric_limits<float>::epsilon();

float Utility::RandomFloat()
{
    return (float)rand() / (float)RAND_MAX;
}

float Utility::RandomFloat(float min, float max)
{
    return min + (max - min) * RandomFloat();
}

float Utility::Clamp(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

float Utility::DegreesToRadians(float degrees)
{
    return degrees * (float)M_PI / 180.0f;
}
