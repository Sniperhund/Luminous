#pragma once

#include "Object.h"
#include <vector>

class BVHNode : public Object
{
public:
    BVHNode(std::vector<Object*> objects, float tMin, float tMax);

    virtual bool Intersect(Ray ray, float tMin, float tMax, HitRecord& hitRecord) override;
    virtual AABB BoundingBox() const override { return box; }

private:
    Object* left;
    Object* right;
    AABB box;
};
