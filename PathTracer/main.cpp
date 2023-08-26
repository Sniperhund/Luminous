#include "Pathtracer.h"
#include "Scene Management/Camera.h"
#include "Scene Management/Objects/RawMesh.h"
#include "Scene Management/Material.h"
#include "Scene Management/Objects/Mesh.h"
#include "Util/Utility.h"

int main(int argc, char* argv[])
{
    Pathtracer pathtracer = Pathtracer(800, 800);
    
    Utility::SamplesPerPixel = 128;
    Utility::MaxDepth = 12;
    Utility::BackgroundColor = Vector3(0.0f, 0.0f, 0.0f);

    Camera::SetPosition(Vector3(5, 0, 0));
    Camera::SetLookAt(Vector3(0, 0, 0));
    Camera::SetVerticalFieldOfView(40.f);

    Scene* scene = new Scene();

    Mesh* højre = new Mesh("CornellsBox/højre.fbx", Vector3(0), new Lambertian(Vector3(.65f, .05f, .05f)));
    Mesh* venstre = new Mesh("CornellsBox/venstre.fbx", Vector3(0), new Lambertian(Vector3(.12f, .45f, .15f)));
    Mesh* top = new Mesh("CornellsBox/top.fbx", Vector3(0), new Lambertian(Vector3(.73f, .73f, .73f)));
    Mesh* bund = new Mesh("CornellsBox/bund.fbx", Vector3(0), new Lambertian(Vector3(.73f, .73f, .73f)));
    Mesh* bag = new Mesh("CornellsBox/bag.fbx", Vector3(0), new Lambertian(Vector3(.73f, .73f, .73f)));
    
    Mesh* lys = new Mesh("CornellsBox/lys.fbx", Vector3(0), new DiffuseLight(Vector3(1.f)));

    scene->AddObject(højre);
    scene->AddObject(venstre);
    scene->AddObject(top);
    scene->AddObject(bund);
    scene->AddObject(bag);

    scene->AddObject(lys);

    pathtracer.RaytraceScene(scene);

    system("output.png");
    
    return 0;
}
