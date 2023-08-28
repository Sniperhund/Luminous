#include "Object.h"

#include "../Material.h"

void HitRecord::SetFaceNormal(Ray ray, glm::vec3 outwardNormal)
{
    frontFace = glm::dot(ray.Direction, outwardNormal) < 0;
    normal = frontFace ? outwardNormal : -outwardNormal;
}
