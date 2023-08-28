#include "RawMesh.h"

bool RawMesh::Intersect(Ray ray, float tMin, float tMax, HitRecord& hitRecord)
{
    float closestT = tMax;
    bool hitAnything = false;

    for (int i = 0; i < Indices.size(); i += 3)
    {
        glm::vec3 v0 = TransformedVertices[Indices[i]];
        glm::vec3 v1 = TransformedVertices[Indices[i + 1]];
        glm::vec3 v2 = TransformedVertices[Indices[i + 2]];

        float triangleT = 0;

        if (IntersectTriangle(ray, v0, v1, v2, tMin, tMax, triangleT))
        {
            if (triangleT < closestT && triangleT < tMax)
            {
                closestT = triangleT;
                hitAnything = true;

                glm::vec3 outwardNormal = glm::normalize(glm::cross(v1 - v0, v2 - v0));  // Ensure normalized outward normal
                if (glm::dot(outwardNormal, ray.Direction) > 0)
                    outwardNormal = -outwardNormal;  // Reverse the normal if it's pointing away from the ray

                hitRecord.SetFaceNormal(ray, outwardNormal);
                hitRecord.time = triangleT;
                hitRecord.material = material;
                hitRecord.position = ray.At(closestT);
            }
        }
    }

    return hitAnything;
}

AABB RawMesh::BoundingBox() const
{
    glm::vec3 minBound = glm::vec3(std::numeric_limits<float>::max());
    glm::vec3 maxBound = glm::vec3(-std::numeric_limits<float>::max());

    for (const glm::vec3& vertex : TransformedVertices)
    {
        minBound = glm::min(minBound, vertex);
        minBound *= 1.1f;  // Ensure the bounding box is slightly smaller than the mesh
        maxBound = glm::max(maxBound, vertex);
    }

    return AABB(minBound, maxBound);
}

void RawMesh::SetPosition(glm::vec3 position)
{
    Object::SetPosition(position);
    TransformVertices();
}

void RawMesh::SetRotation(glm::vec3 rotation)
{
    Object::SetRotation(rotation);
    TransformVertices();
}

void RawMesh::SetScale(glm::vec3 scale)
{
    Object::SetScale(scale);
    TransformVertices();
}

bool RawMesh::IntersectTriangle(Ray ray, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, float tmin, float tmax, float& t)
{
    t = 0.0f;

    glm::vec3 edge1 = v1 - v0;
    glm::vec3 edge2 = v2 - v0;

    glm::vec3 h = glm::cross(ray.Direction, edge2);
    float a = glm::dot(edge1, h);

    if (a > -0.00001f && a < 0.00001f)
    {
        return false;
    }

    float f = 1.0f / a;
    glm::vec3 s = ray.Origin - v0;
    float u = f * glm::dot(s, h);

    if (u < 0.0f || u > 1.0f)
    {
        return false;
    }

    glm::vec3 q = glm::cross(s, edge1);
    float v = f * glm::dot(ray.Direction, q);

    if (v < 0.0f || u + v > 1.0f)
    {
        return false;
    }

    float tValue = f * glm::dot(edge2, q);

    if (tValue > 0.00001f && tValue > tmin && tValue < tmax)
    {
        t = tValue;
        return true;
    }

    return false;
}

glm::vec3 RawMesh::RotateAndScale(glm::vec3 vector)
{
    float cosThetaX = cos(m_rotation.x);
    float sinThetaX = sin(m_rotation.x);
    float cosThetaY = cos(m_rotation.y);
    float sinThetaY = sin(m_rotation.y);
    float cosThetaZ = cos(m_rotation.z);
    float sinThetaZ = sin(m_rotation.z);

    glm::vec3 rotatedVector;
    rotatedVector.x = (cosThetaY * cosThetaZ) * vector.x + (cosThetaZ * sinThetaX * sinThetaY - cosThetaX * sinThetaZ) * vector.y + (cosThetaX * cosThetaZ * sinThetaY + sinThetaX * sinThetaZ) * vector.z;
    rotatedVector.y = (cosThetaY * sinThetaZ) * vector.x + (cosThetaX * cosThetaZ + sinThetaX * sinThetaY * sinThetaZ) * vector.y + (-cosThetaZ * sinThetaX + cosThetaX * sinThetaY * sinThetaZ) * vector.z;
    rotatedVector.z = (-sinThetaY) * vector.x + (cosThetaY * sinThetaX) * vector.y + (cosThetaX * cosThetaY) * vector.z;

    rotatedVector *= m_scale;

    rotatedVector += m_position;

    return rotatedVector;
}

void RawMesh::TransformVertices()
{
    for (int i = 0; i < 4; i++)
    {
        TransformedVertices[i] = RotateAndScale(Vertices[i]);
    }
}
