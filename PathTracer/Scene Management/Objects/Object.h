#pragma once
#include "AABB.h"
#include "../../Math/Ray.h"

class Material;

struct HitRecord
{
    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec3 normal = glm::vec3(0, 0, 0);
    float time = 0.0f, u = 0.0f, v = 0.0f;
    bool frontFace = false;
    Material* material = nullptr;

    void SetFaceNormal(Ray ray, glm::vec3 outwardNormal);
};

class Object
{
public:
    Material* material;

    Object(Material* material) : material(material) {}

    virtual bool Intersect(Ray ray, float tMin, float tMax, HitRecord& hitRecord) = 0;
    virtual AABB BoundingBox() const = 0;

    virtual void SetPosition(glm::vec3 position) { m_position = position; }
    virtual void SetRotation(glm::vec3 rotation) { m_rotation = rotation; }
    virtual void SetScale(glm::vec3 scale) { m_scale = scale; }

    glm::vec3 GetPosition() { return m_position; }
    glm::vec3 GetRotation() { return m_rotation; }
    glm::vec3 GetScale() { return m_scale; }
protected:
    glm::vec3 m_position = glm::vec3(0);
    glm::vec3 m_rotation = glm::vec3(0);
    glm::vec3 m_scale = glm::vec3(1);
};
