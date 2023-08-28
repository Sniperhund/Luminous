#include "Utility.h"

#include <corecrt_math_defines.h>
#include <cstdlib>

int Utility::SamplesPerPixel = 1024;
int Utility::MaxDepth = 4;
glm::vec3 Utility::BackgroundColor = glm::vec3(0.5f, 0.5f, 0.5f);

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

bool Utility::NearZero(glm::vec3 vector)
{
    auto s = 1e-8;
    return (fabs(vector.x) < s) && (fabs(vector.y) < s) && (fabs(vector.z) < s);
}

glm::vec3 Utility::Random()
{
    return glm::vec3(Utility::RandomFloat(), Utility::RandomFloat(), Utility::RandomFloat());
}

glm::vec3 Utility::Random(float min, float max)
{
    return glm::vec3(Utility::RandomFloat(min, max), Utility::RandomFloat(min, max), Utility::RandomFloat(min, max));
}

glm::vec3 Utility::RandomUnitVector()
{
    return glm::normalize(RandomInUnitSphere());
}

glm::vec3 Utility::RandomInUnitSphere()
{
    while (true)
    {
        glm::vec3 v = Random(-1, 1);
        if (glm::length(v) * glm::length(v) < 1) return v;
    }
}

glm::vec3 Utility::RandomInUnitDisk()
{
    while (true)
    {
        glm::vec3 p = glm::vec3(Utility::RandomFloat(-1, 1), Utility::RandomFloat(-1, 1), 0);
        if (glm::length(p) * glm::length(p) < 1) return p;
    }
}

glm::vec3 Utility::RandomInUnitVector()
{
    return glm::normalize(RandomInUnitSphere());
}

glm::vec3 Utility::RandomInHemisphere(glm::vec3 normal)
{
    glm::vec3 inUnitSphere = RandomInUnitSphere();
    if (glm::dot(inUnitSphere, normal) > 0.0f)
        return inUnitSphere;
    
    return -inUnitSphere;
}