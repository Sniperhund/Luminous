#include "Pathtracer.h"
#include "Scene Management/Camera.h"
#include "Scene Management/Objects/RawMesh.h"
#include "Scene Management/Material.h"
#include "Scene Management/Objects/Mesh.h"

int main(int argc, char* argv[])
{
    Pathtracer pathtracer = Pathtracer(800, 600);

    Camera::SetPosition(Vector3(0, 0, 3.f));

    Scene* scene = new Scene();

    Mesh* cube = new Mesh("cube.fbx", Vector3(0, -2, 0), new Metal(Vector3(0.8f, 0.8f, 0.5f), 0.8f));
    Mesh* sphere = new Mesh("sphere.fbx", Vector3(0, 0, 0), new Lambertian(Vector3(0.5f, 0.5f, 0.5f)));

    scene->AddObject(cube);
    scene->AddObject(sphere);

    pathtracer.RaytraceScene(scene);

    system("output.png");
    
    return 0;
}
