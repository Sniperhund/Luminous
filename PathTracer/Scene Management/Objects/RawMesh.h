#pragma once
#include <vector>

#include "Object.h"

class RawMesh : public Object
{
public:
    std::vector<Vector3> Vertices;
    std::vector<int> Indices;

    RawMesh(Vector3 position, Material* material, std::vector<Vector3> vertices, std::vector<int> indices);
    bool Intersect(Ray ray, float tMin, float tMax, HitRecord& hitRecord) override;

private:
    bool IntersectTriangle(Ray ray, Vector3 v0, Vector3 v1, Vector3 v2, float tmin, float tmax, float& t);
};