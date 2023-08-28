#pragma once
#include <limits>
#include <glm/glm.hpp>

class Utility
{
public:
    static int SamplesPerPixel;
    static int MaxDepth;
    static glm::vec3 BackgroundColor;
    static float Epsilon;
    
    static float RandomFloat();
    static float RandomFloat(float min, float max);

    static float Clamp(float value, float tMin, float tMax);

    static float DegreesToRadians(float degrees);

    static bool NearZero(glm::vec3 vector);

    static glm::vec3 Random();
    static glm::vec3 Random(float min, float max);
    static glm::vec3 RandomUnitVector();
    static glm::vec3 RandomInUnitSphere();
    static glm::vec3 RandomInUnitDisk();
    static glm::vec3 RandomInUnitVector();
    static glm::vec3 RandomInHemisphere(glm::vec3 normal);
};
