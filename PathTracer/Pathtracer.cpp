#include "Pathtracer.h"

#include "Scene Management/Camera.h"
#include "Util/Utility.h"
#include "Scene Management/Material.h"

#include <BS_thread_pool.hpp>

Pathtracer::Pathtracer(int width, int height) : m_image(Image(width, height))
{
    m_width = width;
    m_height = height;

    Camera::Initialize(width, height);
}

void Pathtracer::RaytraceScene(Scene* scene)
{
    BS::thread_pool pool(std::thread::hardware_concurrency() - 2);
    
    for (int y = 0; y < m_height; y++)
    {
        pool.submit([this, scene, y]
        {
            for (int x = 0; x < m_width; x++)
            {
                Vector3 color = Vector3(0, 0, 0);

                for (int samples = 0; samples < Utility::SamplesPerPixel; samples++)
                {
                    Ray ray = Camera::GetRay(x, y);
                    color += TraceRay(ray, Utility::MaxDepth, scene);
                }

                float scale = 1.0f / Utility::SamplesPerPixel;

                color.x = sqrtf(scale * color.x);
                color.y = sqrtf(scale * color.y);
                color.z = sqrtf(scale * color.z);

                m_image.SetPixel(x, y, color);
            }
        });
    }

    pool.wait_for_tasks();

    m_image.Save("output.png");
}

Vector3 Pathtracer::TraceRay(Ray ray, int depth, Scene* scene)
{
    HitRecord hitRecord;

    if (depth <= 0)
        return Vector3::Zero();

    if (scene->Intersect(ray, 0.001f, 10000.0f, hitRecord))
    {
        Ray scattered;
        Vector3 attenuation;
        if (hitRecord.material->Scatter(ray, hitRecord, attenuation, scattered))
            return attenuation * TraceRay(scattered, depth - 1, scene);

        return Vector3(0);
    }

    Vector3 unitDirection = Vector3::Normalize(ray.Direction);
    float a = 0.5f * (unitDirection.y + 1.0f);
    return (1.0f - a) * Vector3(1.0f) + a * Vector3(0.5f, 0.7f, 1.0f);
}
