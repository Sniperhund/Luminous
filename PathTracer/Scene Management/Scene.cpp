#include "Scene.h"

void Scene::AddObject(Object* object)
{
    objects.push_back(object);
}

bool Scene::Intersect(Ray ray, float tMin, float tMax, HitRecord& hitRecord) const
{
    bool hitAnything = false;
    float closestSoFar = tMax;
    HitRecord tempHitRecord;
    
    for (auto object : objects)
    {
        if (object->Intersect(ray, tMin, closestSoFar, tempHitRecord))
        {
            hitAnything = true;
            closestSoFar = tempHitRecord.time;
            hitRecord = tempHitRecord;
        }
    }

    return hitAnything;
}
