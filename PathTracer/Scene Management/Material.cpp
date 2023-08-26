#include "Material.h"

bool Lambertian::Scatter(Ray ray, HitRecord hitRecord, Vector3& attenuation, Ray& scattered) const
{
    Vector3 scatterDirection = hitRecord.normal + Vector3::RandomUnitVector();

    if (Vector3::NearZero(scatterDirection))
        scatterDirection = hitRecord.normal;

    scattered = Ray(hitRecord.position, scatterDirection);
    attenuation = Albedo;
    return true;
}

bool Metal::Scatter(Ray ray, HitRecord hitRecord, Vector3& attenuation, Ray& scattered) const
{
    Vector3 reflected = Vector3::Reflect(Vector3::Normalize(ray.Direction), hitRecord.normal);
    scattered = Ray(hitRecord.position, reflected);
    attenuation = Albedo;
    return true;
}
