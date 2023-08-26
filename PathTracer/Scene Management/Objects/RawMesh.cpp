#include "RawMesh.h"

RawMesh::RawMesh(Vector3 position, Material* material, std::vector<Vector3> vertices, std::vector<int> indices) : Object(material)
{
    Vertices = vertices;
    Indices = indices;
}

bool RawMesh::Intersect(Ray ray, float tMin, float tMax, HitRecord& hitRecord)
{
    float closestT = tMax;
    bool hitAnything = false;

    for (int i = 0; i < Indices.size(); i += 3)
    {
        Vector3 v0 = Vertices[Indices[i]] + position;
        Vector3 v1 = Vertices[Indices[i + 1]] + position;
        Vector3 v2 = Vertices[Indices[i + 2]] + position;

        float triangleT;

        if (IntersectTriangle(ray, v0, v1, v2, tMin, tMax, triangleT))
        {
            if (triangleT < closestT && triangleT < tMax)
            {
                closestT = triangleT;
                hitAnything = true;

                Vector3 outwardNormal = Vector3::Cross(v1 - v0, v2 - v0);
                hitRecord.SetFaceNormal(ray, outwardNormal);
                hitRecord.time = triangleT;
                hitRecord.material = material;
                hitRecord.position = ray.At(closestT);
            }
        }
    }

    return hitAnything;
}

bool RawMesh::IntersectTriangle(Ray ray, Vector3 v0, Vector3 v1, Vector3 v2, float tmin, float tmax, float& t)
{
    t = 0.0f;

    Vector3 edge1 = v1 - v0;
    Vector3 edge2 = v2 - v0;

    Vector3 h = Vector3::Cross(ray.Direction, edge2);
    float a = Vector3::Dot(edge1, h);

    if (a > -0.00001f && a < 0.00001f)
    {
        return false;
    }

    float f = 1.0f / a;
    Vector3 s = ray.Origin - v0;
    float u = f * Vector3::Dot(s, h);

    if (u < 0.0f || u > 1.0f)
    {
        return false;
    }

    Vector3 q = Vector3::Cross(s, edge1);
    float v = f * Vector3::Dot(ray.Direction, q);

    if (v < 0.0f || u + v > 1.0f)
    {
        return false;
    }

    float tValue = f * Vector3::Dot(edge2, q);

    if (tValue > 0.00001f && tValue > tmin && tValue < tmax)
    {
        t = tValue;
        return true;
    }

    return false;
}