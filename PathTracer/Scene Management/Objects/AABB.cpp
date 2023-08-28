#include "AABB.h"

bool AABB::Intersect(const Ray& ray, float tMin, float tMax) const
{
    for (int i = 0; i < 3; ++i) {
        float invD = 1.0f / ray.Direction[i];
        float t0 = (min[i] - ray.Origin[i]) * invD;
        float t1 = (max[i] - ray.Origin[i]) * invD;
        if (invD < 0.0f) {
            std::swap(t0, t1);
        }
        tMin = t0 > tMin ? t0 : tMin;
        tMax = t1 < tMax ? t1 : tMax;
        if (tMax <= tMin) {
            return false;
        }
    }
    return true;
}

AABB SurroundingBox(const AABB& box1, const AABB& box2)
{
    glm::vec3 small(std::fmin(box1.min.x, box2.min.x),
                    std::fmin(box1.min.y, box2.min.y),
                    std::fmin(box1.min.z, box2.min.z));
    glm::vec3 big(std::fmax(box1.max.x, box2.max.x),
                  std::fmax(box1.max.y, box2.max.y),
                  std::fmax(box1.max.z, box2.max.z));
    return AABB(small, big);
}
