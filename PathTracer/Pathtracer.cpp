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
    
    int totalPixels = m_width * m_height;
    std::atomic<int> processedPixels(0);
    
    int updateInterval = totalPixels / 100;  // Update every 1% progress
    
    for (int y = 0; y < m_height; y++)
    {
        // ReSharper disable once CppNoDiscardExpression
        pool.submit([this, scene, y, &processedPixels, updateInterval, totalPixels]
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

                // Update the processed pixel count
                int pixelsProcessed = ++processedPixels;

                // Update the progress bar at specified intervals
                if (pixelsProcessed % updateInterval == 0 || pixelsProcessed == totalPixels)
                {
                    float progress = static_cast<float>(pixelsProcessed) / totalPixels * 100;
                    std::cout << "\rProgress: " << std::fixed << std::setprecision(2) << progress << "%";
                    std::cout.flush();
                }
            }
        });
    }

    pool.wait_for_tasks();

    std::cout << "\rProgress: 100.00%" << std::endl;

    m_image.Save("output.png");
}

Vector3 Pathtracer::TraceRay(Ray ray, int depth, Scene* scene)
{
    HitRecord hitRecord;

    if (depth <= 0)
        return Vector3::Zero();

    if (!scene->Intersect(ray, 0.00001f, 1000000.0f, hitRecord))
        return Utility::BackgroundColor;

    Ray scattered;
    Vector3 attenuation;
    Vector3 emitted = hitRecord.material->Emitted(hitRecord.u, hitRecord.v, hitRecord.position);

    if (!hitRecord.material->Scatter(ray, hitRecord, attenuation, scattered))
        return emitted;

    Vector3 color = attenuation * TraceRay(scattered, depth - 1, scene);

    return emitted + color;
}
