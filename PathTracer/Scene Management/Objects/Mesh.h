#pragma once

#include <string>
#include <assimp/scene.h>

#include "RawMesh.h"

class Mesh : public RawMesh
{
public:
    Mesh(std::string filename, Vector3 position, Material* material);

private:
    void ProcessNode(aiNode* node, const aiScene* scene);
    void ProcessMesh(aiMesh* mesh, const aiScene* scene);
};
