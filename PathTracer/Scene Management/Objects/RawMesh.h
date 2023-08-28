#pragma once
#include <vector>

#include "Object.h"

class RawMesh : public Object
{
public:
    RawMesh(Material* material) : Object(material)
    {
    }

    std::vector<glm::vec3> Vertices = std::vector<glm::vec3>();
    std::vector<int> Indices = std::vector<int>();
    
    bool Intersect(Ray ray, float tMin, float tMax, HitRecord& hitRecord) override;
    AABB BoundingBox() const override;

    void SetPosition(glm::vec3 position) override;
    void SetRotation(glm::vec3 rotation) override;
    void SetScale(glm::vec3 scale) override;

protected:
    friend class Mesh;
    std::vector<glm::vec3> TransformedVertices;
    
private:
    bool IntersectTriangle(Ray ray, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, float tmin, float tmax, float& t);
    glm::vec3 RotateAndScale(glm::vec3 vector);

    void TransformVertices();
};
