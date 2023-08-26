#pragma once
#include "../Math/Ray.h"
#include "../Math/Vector3.h"

class Camera
{
public:
    static void Initialize(int width, int height);
    
    static void SetPosition(const Vector3& position);
    static void SetFocalLength(float focalLength);
    static void SetVerticalFieldOfView(float vfov);

    static Ray GetRay(int x, int y);
    
private:
    static void Recalculate();

    static Vector3 PixelSampleSquare();

    static float sm_vfox;
    
    static Vector3 sm_position;
    static float sm_focalLength;

    static float sm_aspectRatio;

    static Vector3 sm_pixel00Location;
    static Vector3 sm_pixelDeltaU;
    static Vector3 sm_pixelDeltaV;

    static int sm_width;
    static int sm_height;
};
