#pragma once
#include "../../Math/Ray.h"
#include "../../Math/Vector3.h"

class Material;

struct HitRecord
{
    Vector3 position = Vector3(0, 0, 0);
    Vector3 normal = Vector3(0, 0, 0);
    float time = 0.0f;
    bool frontFace = false;
    Material* material = nullptr;

    void SetFaceNormal(Ray ray, Vector3 outwardNormal);
};

class Object
{
public:
    Vector3 position = Vector3::Zero();
    Vector3 rotation = Vector3::Zero(); // In radians
    Vector3 scale = Vector3::One();
    Material* material;

    Object(Material* material) : material(material) {}

    virtual bool Intersect(Ray ray, float tMin, float tMax, HitRecord& hitRecord) = 0;
};
