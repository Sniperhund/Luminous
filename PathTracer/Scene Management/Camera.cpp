#include "Camera.h"

#include "../Util/Utility.h"

#define _USE_MATH_DEFINES
#include <math.h>

float Camera::sm_vfov = 90.0f;

glm::vec3 Camera::sm_position = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Camera::sm_lookAt = glm::vec3(0.0f, 0.0f, 0.0f);

float Camera::sm_defocusAngle = 0.0f;
float Camera::sm_focusDist = 10.0f;

glm::vec3 Camera::sm_up = glm::vec3(0.0f, 0.0f, 1.0f);

glm::vec3 Camera::u = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Camera::v = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Camera::w = glm::vec3(0.0f, 0.0f, 0.0f);

float Camera::sm_aspectRatio = 1.0f;

glm::vec3 Camera::sm_pixel00Location = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Camera::sm_pixelDeltaU = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Camera::sm_pixelDeltaV = glm::vec3(0.0f, 0.0f, 0.0f);

glm::vec3 Camera::sm_defocusDiskU = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Camera::sm_defocusDiskV = glm::vec3(0.0f, 0.0f, 0.0f);

int Camera::sm_width = 0;
int Camera::sm_height = 0;

void Camera::Initialize(int width, int height)
{
    sm_aspectRatio = (float)width / (float)height;

    sm_width = width;
    sm_height = height;

    Recalculate();
}

void Camera::SetPosition(const glm::vec3& position)
{
    sm_position = position;
    Recalculate();
}

void Camera::SetVerticalFieldOfView(float vfov)
{
    sm_vfov = vfov;
    Recalculate();
}

void Camera::SetLookAt(const glm::vec3& lookAt)
{
    sm_lookAt = lookAt;
    Recalculate();
}

void Camera::SetDefocusAngle(float defocusAngle)
{
    sm_defocusAngle = defocusAngle;
    Recalculate();
}

void Camera::SetFocusDistance(float focusDistance)
{
    sm_focusDist = focusDistance;
    Recalculate();
}

Ray Camera::GetRay(int x, int y)
{
    glm::vec3 pixelLocation = sm_pixel00Location + sm_pixelDeltaU * (float)x + sm_pixelDeltaV * (float)y;
    glm::vec3 pixelDirection = (pixelLocation + PixelSampleSquare()) - sm_position;

    glm::vec3 rayOrigin = (sm_defocusAngle <= 0) ? sm_position : PixelSampleDisk();

    return Ray(rayOrigin, pixelDirection);
}

void Camera::Recalculate()
{
    float theta = Utility::DegreesToRadians(sm_vfov);
    float h = tan(theta / 2);
    float viewportHeight = 2.0f * h * sm_focusDist;
    float viewportWidth = sm_aspectRatio * viewportHeight;

    w = glm::normalize(sm_position - sm_lookAt);
    u = glm::normalize(glm::cross(sm_up, w));
    v = glm::cross(w, u);

    glm::vec3 viewportU = viewportWidth * u;
    glm::vec3 viewportV = viewportHeight * -v;

    sm_pixelDeltaU = viewportU / (float)sm_width;
    sm_pixelDeltaV = viewportV / (float)sm_height;

    auto viewportUpperLeft = sm_position - (sm_focusDist * w) - viewportU / 2.0f - viewportV / 2.0f;
    sm_pixel00Location = viewportUpperLeft + 0.5f * (sm_pixelDeltaU + sm_pixelDeltaV);

    auto defocusRadius = sm_focusDist * tan(Utility::DegreesToRadians(sm_defocusAngle / 2));
    sm_defocusDiskU = defocusRadius * u;
    sm_defocusDiskV = defocusRadius * v;
}

glm::vec3 Camera::PixelSampleSquare()
{
    float px = -0.5f + Utility::RandomFloat();
    float py = -0.5f + Utility::RandomFloat();
    return (px * sm_pixelDeltaU) + (py * sm_pixelDeltaV);
}

glm::vec3 Camera::PixelSampleDisk()
{
    glm::vec3 p = Utility::RandomInUnitDisk();
    return sm_position + (p.x * sm_defocusDiskU) + (p.y * sm_defocusDiskV);
}
