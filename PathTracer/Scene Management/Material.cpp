#include "Material.h"

#include "../Util/Utility.h"

bool Lambertian::Scatter(Ray ray, HitRecord hitRecord, glm::vec3& attenuation, Ray& scattered) const
{
    glm::vec3 scatterDirection = hitRecord.normal + Utility::RandomUnitVector();

    if (Utility::NearZero(scatterDirection))
        scatterDirection = hitRecord.normal;

    scattered = Ray(hitRecord.position, scatterDirection);
    attenuation = Albedo;
    return true;
}

bool Metal::Scatter(Ray ray, HitRecord hitRecord, glm::vec3& attenuation, Ray& scattered) const
{
    glm::vec3 reflected = glm::reflect(glm::normalize(ray.Direction), hitRecord.normal);
    scattered = Ray(hitRecord.position, reflected);
    attenuation = Albedo;
    return true;
}

bool DiffuseLight::Scatter(Ray ray, HitRecord hitRecord, glm::vec3& attenuation, Ray& scattered) const
{
    return false;
}

glm::vec3 DiffuseLight::Emitted(float u, float v, glm::vec3 position) const
{
    return Albedo;
}
