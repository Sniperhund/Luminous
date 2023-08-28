#pragma once
#include "../Math/Ray.h"
#include "Objects/Object.h"

class Material
{
public:
    glm::vec3 Albedo;

    Material(glm::vec3 albedo) : Albedo(albedo) {}
    Material() : Albedo(glm::vec3(0)) {}

    virtual bool Scatter(Ray ray, HitRecord hitRecord, glm::vec3& attenuation, Ray& scattered) const { return false; };
    virtual glm::vec3 Emitted(float u, float v, glm::vec3 position) const { return glm::vec3(0); }
};

class Lambertian : public Material
{
public:
    Lambertian(glm::vec3 albedo) : Material(albedo) {}

    bool Scatter(Ray ray, HitRecord hitRecord, glm::vec3& attenuation, Ray& scattered) const override;
};

class Metal : public Material
{
public:
    Metal(glm::vec3 albedo, float fuzz) : Material(albedo) { m_fuzz = fuzz; }

    bool Scatter(Ray ray, HitRecord hitRecord, glm::vec3& attenuation, Ray& scattered) const override;

private:
    float m_fuzz;
};

class DiffuseLight : public Material
{
public:
    DiffuseLight(glm::vec3 albedo) : Material(albedo) {}

    bool Scatter(Ray ray, HitRecord hitRecord, glm::vec3& attenuation, Ray& scattered) const override;
    glm::vec3 Emitted(float u, float v, glm::vec3 position) const override;
};