#include "Ray.h"

Ray::Ray(glm::vec3 origin, glm::vec3 direction)
{
    Origin = origin;
    Direction = direction;
}

Ray::Ray()
{
    Ray(glm::vec3(0), glm::vec3(0));
}

glm::vec3 Ray::At(float t) const
{
    return Origin + Direction * t;
}
