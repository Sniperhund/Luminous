#pragma once
#include <vector>

#include "Objects/Object.h"

class Scene
{
public:
    std::vector<Object*> objects = std::vector<Object*>();

    void AddObject(Object* object);
    bool Intersect(Ray ray, float tMin, float tMax, HitRecord& hitRecord) const;
};
