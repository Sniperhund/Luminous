#include "Camera.h"

#include "../Util/Utility.h"

#define _USE_MATH_DEFINES
#include <math.h>

float Camera::sm_vfov = 90.0f;

Vector3 Camera::sm_position = Vector3(0.0f, 0.0f, 0.0f);
Vector3 Camera::sm_lookAt = Vector3(0.0f, 0.0f, 0.0f);

float Camera::sm_defocusAngle = 0.0f;
float Camera::sm_focusDist = 10.0f;

Vector3 Camera::sm_up = Vector3(0.0f, 0.0f, 1.0f);

Vector3 Camera::u = Vector3(0.0f, 0.0f, 0.0f);
Vector3 Camera::v = Vector3(0.0f, 0.0f, 0.0f);
Vector3 Camera::w = Vector3(0.0f, 0.0f, 0.0f);

float Camera::sm_aspectRatio = 1.0f;

Vector3 Camera::sm_pixel00Location = Vector3(0.0f, 0.0f, 0.0f);
Vector3 Camera::sm_pixelDeltaU = Vector3(0.0f, 0.0f, 0.0f);
Vector3 Camera::sm_pixelDeltaV = Vector3(0.0f, 0.0f, 0.0f);

Vector3 Camera::sm_defocusDiskU = Vector3(0.0f, 0.0f, 0.0f);
Vector3 Camera::sm_defocusDiskV = Vector3(0.0f, 0.0f, 0.0f);

int Camera::sm_width = 0;
int Camera::sm_height = 0;

void Camera::Initialize(int width, int height)
{
    sm_aspectRatio = (float)width / (float)height;

    sm_width = width;
    sm_height = height;

    Recalculate();
}

void Camera::SetPosition(const Vector3& position)
{
    sm_position = position;
    Recalculate();
}

void Camera::SetVerticalFieldOfView(float vfov)
{
    sm_vfov = vfov;
    Recalculate();
}

void Camera::SetLookAt(const Vector3& lookAt)
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
    Vector3 pixelLocation = sm_pixel00Location + sm_pixelDeltaU * (float)x + sm_pixelDeltaV * (float)y;
    Vector3 pixelDirection = (pixelLocation + PixelSampleSquare()) - sm_position;

    Vector3 rayOrigin = (sm_defocusAngle <= 0) ? sm_position : PixelSampleDisk();

    return Ray(rayOrigin, pixelDirection);
}

void Camera::Recalculate()
{
    float theta = Utility::DegreesToRadians(sm_vfov);
    float h = tan(theta / 2);
    float viewportHeight = 2.0f * h * sm_focusDist;
    float viewportWidth = sm_aspectRatio * viewportHeight;

    w = Vector3::Normalize(sm_position - sm_lookAt);
    u = Vector3::Normalize(Vector3::Cross(sm_up, w));
    v = Vector3::Cross(w, u);

    Vector3 viewportU = viewportWidth * u;
    Vector3 viewportV = viewportHeight * -v;

    sm_pixelDeltaU = viewportU / (float)sm_width;
    sm_pixelDeltaV = viewportV / (float)sm_height;

    auto viewportUpperLeft = sm_position - (sm_focusDist * w) - viewportU / 2 - viewportV / 2;
    sm_pixel00Location = viewportUpperLeft + 0.5f * (sm_pixelDeltaU + sm_pixelDeltaV);

    auto defocusRadius = sm_focusDist * tan(Utility::DegreesToRadians(sm_defocusAngle / 2));
    sm_defocusDiskU = defocusRadius * u;
    sm_defocusDiskV = defocusRadius * v;
}

Vector3 Camera::PixelSampleSquare()
{
    float px = -0.5f + Utility::RandomFloat();
    float py = -0.5f + Utility::RandomFloat();
    return (px * sm_pixelDeltaU) + (py * sm_pixelDeltaV);
}

Vector3 Camera::PixelSampleDisk()
{
    Vector3 p = Vector3::RandomInUnitDisk();
    return sm_position + (p.x * sm_defocusDiskU) + (p.y * sm_defocusDiskV);
}
