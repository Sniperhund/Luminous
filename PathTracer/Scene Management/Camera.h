#pragma once
#include "../Math/Ray.h"

class Camera
{
public:
    static void Initialize(int width, int height);
    
    static void SetPosition(const glm::vec3& position);
    static void SetVerticalFieldOfView(float vfov);
    static void SetLookAt(const glm::vec3& lookAt);
    static void SetDefocusAngle(float defocusAngle);
    static void SetFocusDistance(float focusDistance);

    static Ray GetRay(int x, int y);
    
private:
    static void Recalculate();
    
    static glm::vec3 PixelSampleSquare();
    static glm::vec3 PixelSampleDisk();

    // User editable:
    static float sm_vfov;
    
    static glm::vec3 sm_position;
    static glm::vec3 sm_lookAt;

    static float sm_defocusAngle;
    static float sm_focusDist;
    
    // Internal:
    static glm::vec3 sm_up;

    static glm::vec3 u, v, w;

    static float sm_aspectRatio;

    static glm::vec3 sm_pixel00Location;
    static glm::vec3 sm_pixelDeltaU;
    static glm::vec3 sm_pixelDeltaV;

    static glm::vec3 sm_defocusDiskU;
    static glm::vec3 sm_defocusDiskV;

    static int sm_width;
    static int sm_height;
};
