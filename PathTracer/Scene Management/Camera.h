#pragma once
#include "../Math/Ray.h"
#include "../Math/Vector3.h"

class Camera
{
public:
    static void Initialize(int width, int height);
    
    static void SetPosition(const Vector3& position);
    static void SetVerticalFieldOfView(float vfov);
    static void SetLookAt(const Vector3& lookAt);
    static void SetDefocusAngle(float defocusAngle);
    static void SetFocusDistance(float focusDistance);

    static Ray GetRay(int x, int y);
    
private:
    static void Recalculate();
    
    static Vector3 PixelSampleSquare();
    static Vector3 PixelSampleDisk();

    // User editable:
    static float sm_vfov;
    
    static Vector3 sm_position;
    static Vector3 sm_lookAt;

    static float sm_defocusAngle;
    static float sm_focusDist;
    
    // Internal:
    static Vector3 sm_up;

    static Vector3 u, v, w;

    static float sm_aspectRatio;

    static Vector3 sm_pixel00Location;
    static Vector3 sm_pixelDeltaU;
    static Vector3 sm_pixelDeltaV;

    static Vector3 sm_defocusDiskU;
    static Vector3 sm_defocusDiskV;

    static int sm_width;
    static int sm_height;
};
