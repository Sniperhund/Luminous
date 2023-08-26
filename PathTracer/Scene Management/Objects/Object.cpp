#include "Object.h"

#include "../Material.h"

void HitRecord::SetFaceNormal(Ray ray, Vector3 outwardNormal)
{
    frontFace = Vector3::Dot(ray.Direction, outwardNormal) < 0;
    normal = frontFace ? outwardNormal : -outwardNormal;
}
