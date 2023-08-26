#pragma once

class Vector3
{
public:
    float x = 0, y = 0, z = 0;

    Vector3(float x, float y, float z);
    Vector3(float v);
    Vector3();

    Vector3 operator-() const;

    bool operator==(const Vector3& v) const;
    
    Vector3& operator+=(const Vector3& v);
    Vector3& operator+=(float v);
    Vector3& operator-=(const Vector3& v);
    Vector3& operator-=(float v);
    Vector3& operator*=(const Vector3& v);
    Vector3& operator*=(float v);
    Vector3& operator/=(const Vector3& v);
    Vector3& operator/=(float v);

    static float Dot(Vector3 v1, Vector3 v2);
    static Vector3 Cross(Vector3 v1, Vector3 v2);
    static Vector3 Normalize(Vector3 v);
    static float Length(Vector3 v);
    static float LengthSquared(Vector3 v);

    static Vector3 Zero();
    static Vector3 One();

    static Vector3 Random();
    static Vector3 Random(float min, float max);
    static Vector3 RandomUnitVector();
    static Vector3 RandomInUnitSphere();
    static Vector3 RandomInUnitVector();
    static Vector3 RandomInHemisphere(Vector3 normal);

    static Vector3 Reflect(Vector3 v, Vector3 normal);
    
    static bool NearZero(Vector3 v);

    static Vector3 Clamp(Vector3 v, float min, float max);
};

Vector3 operator+(Vector3 v1, const Vector3& v2);
Vector3 operator+(Vector3 v1, float v2);
Vector3 operator+(float v1, Vector3 v2);
Vector3 operator-(Vector3 v1, const Vector3& v2);
Vector3 operator-(Vector3 v1, float v2);
Vector3 operator-(float v1, Vector3 v2);
Vector3 operator*(Vector3 v1, const Vector3& v2);
Vector3 operator*(Vector3 v1, float v2);
Vector3 operator*(float v1, Vector3 v2);
Vector3 operator/(Vector3 v1, const Vector3& v2);
Vector3 operator/(Vector3 v1, float v2);
Vector3 operator/(float v1, Vector3 v2);