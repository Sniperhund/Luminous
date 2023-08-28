#pragma once

#include <glm/glm.hpp>

class Ray
{
public:
    glm::vec3 Origin;
    glm::vec3 Direction;

    Ray(glm::vec3 origin, glm::vec3 direction);
    Ray();

    glm::vec3 At(float t) const;
};
