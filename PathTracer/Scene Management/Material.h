#pragma once
#include "../Math/Vector3.h"
#include "../Math/Ray.h"
#include "Objects/Object.h"

class Material
{
public:
    Vector3 Albedo;

    Material(Vector3 albedo) : Albedo(albedo) {}
    Material() : Albedo(Vector3(0)) {}

    virtual bool Scatter(Ray ray, HitRecord hitRecord, Vector3& attenuation, Ray& scattered) const = 0;
    virtual Vector3 Emitted(float u, float v, Vector3 position) const { return Vector3(0); }
};

class Lambertian : public Material
{
public:
    Lambertian(Vector3 albedo) : Material(albedo) {}

    bool Scatter(Ray ray, HitRecord hitRecord, Vector3& attenuation, Ray& scattered) const override;
};

class Metal : public Material
{
public:
    Metal(Vector3 albedo, float fuzz) : Material(albedo) { m_fuzz = fuzz; }

    bool Scatter(Ray ray, HitRecord hitRecord, Vector3& attenuation, Ray& scattered) const override;

private:
    float m_fuzz;
};

class DiffuseLight : public Material
{
public:
    DiffuseLight(Vector3 albedo) : Material(albedo) {}

    bool Scatter(Ray ray, HitRecord hitRecord, Vector3& attenuation, Ray& scattered) const override;
    Vector3 Emitted(float u, float v, Vector3 position) const override;
};