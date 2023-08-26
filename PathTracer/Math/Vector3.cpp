#include "Vector3.h"

#include "../Util/Utility.h"

#include <complex>

Vector3::Vector3(float x, float y, float z)
{
    this->x = x; this->y = y; this->z = z;
}

Vector3::Vector3(float v)
{
    this->x = v; this->y = v; this->z = v;
}

Vector3::Vector3()
{
    Vector3(0);
}

Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

bool Vector3::operator==(const Vector3& v) const
{
    return x == v.x && y == v.y && z == v.z;
}

Vector3& Vector3::operator+=(const Vector3& v)
{
    x += v.x; y += v.y; z += v.z;
    return *this;
}

Vector3& Vector3::operator+=(float v)
{
    x += v; y += v; z += v;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
    x -= v.x; y -= v.y; z -= v.z;
    return *this;
}

Vector3& Vector3::operator-=(float v)
{
    x -= v; y -= v; z -= v;
    return *this;
}

Vector3& Vector3::operator*=(const Vector3& v)
{
    x *= v.x; y *= v.y; z *= v.z;
    return *this;
}

Vector3& Vector3::operator*=(float v)
{
    x *= v; y *= v; z *= v;
    return *this;
}

Vector3& Vector3::operator/=(const Vector3& v)
{
    x /= v.x; y /= v.y; z /= v.z;
    return *this;
}

Vector3& Vector3::operator/=(float v)
{
    x /= v; y /= v; z /= v;
    return *this;
}

float Vector3::Dot(Vector3 v1, Vector3 v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Vector3::Cross(Vector3 v1, Vector3 v2)
{
    return Vector3(v1.y * v2.z - v1.z * v2.y,
                   v1.z * v2.x - v1.x * v2.z,
                   v1.x * v2.y - v1.y * v2.x);
}

Vector3 Vector3::Normalize(Vector3 v)
{
    float length = Length(v);
    return Vector3(v.x / length, v.y / length, v.z / length);
}

float Vector3::Length(Vector3 v)
{
    return std::sqrt(LengthSquared(v));
}

float Vector3::LengthSquared(Vector3 v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

Vector3 Vector3::Zero()
{
    return Vector3(0);
}

Vector3 Vector3::One()
{
    return Vector3(1);
}

Vector3 Vector3::Random()
{
    return Vector3(Utility::RandomFloat(), Utility::RandomFloat(), Utility::RandomFloat());
}

Vector3 Vector3::Random(float min, float max)
{
    return Vector3(Utility::RandomFloat(min, max), Utility::RandomFloat(min, max), Utility::RandomFloat(min, max));
}

Vector3 Vector3::RandomUnitVector()
{
    return Normalize(RandomInUnitSphere());
}

Vector3 Vector3::RandomInUnitSphere()
{
    while (true)
    {
        Vector3 v = Random(-1, 1);
        if (LengthSquared(v) < 1) return v;
    }
}

Vector3 Vector3::RandomInUnitDisk()
{
    while (true)
    {
        Vector3 p = Vector3(Utility::RandomFloat(-1, 1), Utility::RandomFloat(-1, 1), 0);
        if (LengthSquared(p) < 1) return p;
    }
}

Vector3 Vector3::RandomInUnitVector()
{
    return Normalize(RandomInUnitSphere());
}

Vector3 Vector3::RandomInHemisphere(Vector3 normal)
{
    Vector3 inUnitSphere = RandomInUnitSphere();
    if (Dot(inUnitSphere, normal) > 0.0f)
        return inUnitSphere;
    
    return -inUnitSphere;
}

Vector3 Vector3::Reflect(Vector3 v, Vector3 normal)
{
    return v - 2 * Dot(v, normal) * normal;
}

bool Vector3::NearZero(Vector3 v)
{
    auto s = 1e-8;
    return (fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s);
}

Vector3 Vector3::Clamp(Vector3 v, float min, float max)
{
    Vector3 clamped = v;
    clamped.x = Utility::Clamp(clamped.x, min, max);
    clamped.y = Utility::Clamp(clamped.y, min, max);
    clamped.z = Utility::Clamp(clamped.z, min, max);
    return clamped;
}

Vector3 operator+(Vector3 v1, const Vector3& v2)
{
    return v1 += v2;
}

Vector3 operator+(Vector3 v1, float v2)
{
    return v1 += v2;
}

Vector3 operator+(float v1, Vector3 v2)
{
    return v2 += v1;
}

Vector3 operator-(Vector3 v1, const Vector3& v2)
{
    return v1 -= v2;
}

Vector3 operator-(Vector3 v1, float v2)
{
    return v1 -= v2;
}

Vector3 operator-(float v1, Vector3 v2)
{
    return v2 -= v1;
}

Vector3 operator*(Vector3 v1, const Vector3& v2)
{
    return v1 *= v2;
}

Vector3 operator*(Vector3 v1, float v2)
{
    return v1 *= v2;
}

Vector3 operator*(float v1, Vector3 v2)
{
    return v2 *= v1;
}

Vector3 operator/(Vector3 v1, const Vector3& v2)
{
    return v1 /= v2;
}

Vector3 operator/(Vector3 v1, float v2)
{
    return v1 /= v2;
}

Vector3 operator/(float v1, Vector3 v2)
{
    return v2 /= v1;
}
