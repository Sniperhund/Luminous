#include <chrono>
#include <corecrt_math_defines.h>
#include <iostream>

#include "Pathtracer.h"
#include "Scene Management/Camera.h"
#include "Scene Management/Objects/RawMesh.h"
#include "Scene Management/Material.h"
#include "Scene Management/Objects/BVHNode.h"
#include "Scene Management/Objects/Mesh.h"
#include "Util/Utility.h"

int main(int argc, char* argv[])
{
    Pathtracer pathtracer = Pathtracer(1000, 1000);
    
    Utility::SamplesPerPixel = 1024 * 16;
    Utility::MaxDepth = 4;
    Utility::BackgroundColor = glm::vec3(0);

    Camera::SetPosition(glm::vec3(4, 0, 0));
    Camera::SetLookAt(glm::vec3(0, 0, 0));
    Camera::SetVerticalFieldOfView(40.f);

    Scene* scene = new Scene();

    Material* red = new Lambertian(glm::vec3(.65f, 0.05f, 0.05f));
    Material* white = new Lambertian(glm::vec3(.73f));
    Material* green = new Lambertian(glm::vec3(.12f, .45f, .15f));
    Material* light = new DiffuseLight(glm::vec3(1));

    std::vector<Object*> objects = std::vector<Object*>();
    
    Mesh* bottom = new Mesh("plane.fbx", white);
    bottom->SetPosition(glm::vec3(0, 0, -1));
    objects.push_back(bottom);

    Mesh* top = new Mesh("plane.fbx", white);
    top->SetPosition(glm::vec3(0, 0, 1));
    objects.push_back(top);

    Mesh* back = new Mesh("plane.fbx", white);
    back->SetPosition(glm::vec3(-1, 0, 0));
    back->SetRotation(glm::vec3(0, Utility::DegreesToRadians(90), 0));
    objects.push_back(back);

    Mesh* left = new Mesh("plane.fbx", green);
    left->SetPosition(glm::vec3(0, -1, 0));
    left->SetRotation(glm::vec3(Utility::DegreesToRadians(90), 0, 0));
    objects.push_back(left);

    Mesh* right = new Mesh("plane.fbx", red);
    right->SetPosition(glm::vec3(0, 1, 0));
    right->SetRotation(glm::vec3(Utility::DegreesToRadians(90), 0, 0));
    objects.push_back(right);

    Mesh* topLight = new Mesh("plane.fbx", light);
    topLight->SetPosition(glm::vec3(0, 0, 0.99f));
    topLight->SetScale(glm::vec3(0.25f));
    objects.push_back(topLight);

    Mesh* dick = new Mesh("dick.fbx", white);
    dick->SetPosition(glm::vec3(1, 0, 0));
    objects.push_back(dick);

    BVHNode* bvh = new BVHNode(objects, 0, 1);
    scene->AddObject(bvh);

    auto t1 = std::chrono::high_resolution_clock::now();
    pathtracer.RaytraceScene(scene);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto msInt = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::chrono::duration<float, std::milli> msFloat = t2 - t1;

    std::cout << msInt.count() << "ms\n";
    std::cout << msFloat.count() << "ms\n";

    system("output.png");
    
    return 0;
}
