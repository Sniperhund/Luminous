#pragma once
#include <limits>

#include "../Math/Vector3.h"

class Utility
{
public:
    static int SamplesPerPixel;
    static int MaxDepth;
    static Vector3 BackgroundColor;
    static float Epsilon;
    
    static float RandomFloat();
    static float RandomFloat(float min, float max);

    static float Clamp(float value, float tMin, float tMax);

    static float DegreesToRadians(float degrees);
};
