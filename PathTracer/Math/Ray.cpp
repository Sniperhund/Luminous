#include "Ray.h"

Ray::Ray(Vector3 origin, Vector3 direction)
{
    Origin = origin;
    Direction = direction;
}

Ray::Ray()
{
    Ray(Vector3(0), Vector3(0));
}

Vector3 Ray::At(float t) const
{
    return Origin + Direction * t;
}
