#include "Camera.h"

#include "../Util/Utility.h"

#define _USE_MATH_DEFINES
#include <math.h>

float Camera::sm_vfox = 90.0f;

Vector3 Camera::sm_position = Vector3(0.0f, 0.0f, 0.0f);
float Camera::sm_focalLength = 1.0f;

float Camera::sm_aspectRatio = 1.0f;

Vector3 Camera::sm_pixel00Location = Vector3(0.0f, 0.0f, 0.0f);
Vector3 Camera::sm_pixelDeltaU = Vector3(0.0f, 0.0f, 0.0f);
Vector3 Camera::sm_pixelDeltaV = Vector3(0.0f, 0.0f, 0.0f);

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

void Camera::SetFocalLength(float focalLength)
{
    sm_focalLength = focalLength;
    Recalculate();
}

void Camera::SetVerticalFieldOfView(float vfov)
{
    sm_vfox = vfov;
    Recalculate();
}

Ray Camera::GetRay(int x, int y)
{
    Vector3 pixelLocation = sm_pixel00Location + sm_pixelDeltaU * (float)x + sm_pixelDeltaV * (float)y;
    Vector3 pixelDirection = (pixelLocation + PixelSampleSquare()) - sm_position;

    return Ray(sm_position, pixelDirection);
}

void Camera::Recalculate()
{
    float theta = sm_vfox * (float)M_PI / 180.0f;
    float h = tan(theta / 2.0f);
    float viewportHeight = 2.0f * h * sm_focalLength;
    float viewportWidth = sm_aspectRatio * viewportHeight;

    Vector3 viewportU = Vector3(viewportWidth, 0.0f, 0.0f);
    Vector3 viewportV = Vector3(0.0f, -viewportHeight, 0.0f);

    sm_pixelDeltaU = viewportU / (float)sm_width;
    sm_pixelDeltaV = viewportV / (float)sm_height;

    Vector3 viewportTopLeft = sm_position - viewportU / 2.0f - viewportV / 2.0f - Vector3(0.0f, 0.0f, sm_focalLength);
    sm_pixel00Location = viewportTopLeft + sm_pixelDeltaU / 2.0f + sm_pixelDeltaV / 2.0f;
}

Vector3 Camera::PixelSampleSquare()
{
    float px = -0.5f + Utility::RandomFloat();
    float py = -0.5f + Utility::RandomFloat();
    return (px * sm_pixelDeltaU) + (py * sm_pixelDeltaV);
}
