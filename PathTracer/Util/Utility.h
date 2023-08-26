#pragma once
#include <limits>

class Utility
{
public:
    static int SamplesPerPixel;
    static int MaxDepth;
    static float Epsilon;
    
    static float RandomFloat();
    static float RandomFloat(float min, float max);

    static float Clamp(float value, float tMin, float tMax);
};
