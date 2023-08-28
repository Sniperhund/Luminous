#pragma once

#include <glm/glm.hpp>
#include "../../Math/Ray.h"

class AABB
{
public:
    glm::vec3 min;
    glm::vec3 max;

    AABB() {}
    AABB(const glm::vec3& a, const glm::vec3& b) : min(a), max(b) {}

    bool Intersect(const Ray& ray, float tMin, float tMax) const;
};

// Function to calculate the surrounding AABB of two AABBs
AABB SurroundingBox(const AABB& box1, const AABB& box2);
