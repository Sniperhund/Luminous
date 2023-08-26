#pragma once
#include "Vector3.h"

class Ray
{
public:
    Vector3 Origin;
    Vector3 Direction;

    Ray(Vector3 origin, Vector3 direction);
    Ray();

    Vector3 At(float t) const;
};
