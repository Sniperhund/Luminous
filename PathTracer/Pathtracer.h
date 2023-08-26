#pragma once
#include "Scene Management/Scene.h"
#include "Util/Image.h"

class Pathtracer
{
public:
    Pathtracer(int width, int height);

    void RaytraceScene(Scene* scene);
    
private:
    Vector3 TraceRay(Ray ray, int depth, Scene* scene);
    
    Image m_image;

    int m_width, m_height;
};
