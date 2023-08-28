#include "BVHNode.h"

#include <iostream>

BVHNode::BVHNode(std::vector<Object*> objects, float tMin, float tMax)
    : Object(nullptr)
{
    if (objects.empty()) {
        // Print an error message if the input object list is empty
        std::cout << "BVHNode construction error: No objects provided.\n";
        return;
    }

    // Calculate the bounding box of all objects in the node
    box = objects[0]->BoundingBox(); // Initialize with the first object's bounding box
    for (Object* object : objects) {
        AABB objectBoundingBox = object->BoundingBox();
        if (objectBoundingBox.max != glm::vec3(0) && objectBoundingBox.min != glm::vec3(0)) {
            box = SurroundingBox(box, objectBoundingBox);
        } else {
            // Print an error message if an object's bounding box is invalid
            std::cout << "BVHNode construction error: Invalid bounding box for an object.\n";
        }
    }

    // If there's only one object or the objects fit in a leaf node, create a leaf node
    if (objects.size() == 1) {
        left = right = objects[0];
    } else if (objects.size() == 2) {
        left = objects[0];
        right = objects[1];
    } else {
        // Split objects into two groups and create child BVH nodes recursively
        // You can implement various splitting strategies here, like SAH or middle split
        // For simplicity, here's a basic middle split strategy:
        std::vector<Object*> leftObjects(objects.begin(), objects.begin() + objects.size() / 2);
        std::vector<Object*> rightObjects(objects.begin() + objects.size() / 2, objects.end());

        left = new BVHNode(leftObjects, tMin, tMax);
        right = new BVHNode(rightObjects, tMin, tMax);
    }
}

bool BVHNode::Intersect(Ray ray, float tMin, float tMax, HitRecord& hitRecord)
{
    // Check if the ray intersects with the BVH node's bounding box
    if (!box.Intersect(ray, tMin, tMax)) {
        return false;
    }

    // Intersect with the left and right child nodes
    HitRecord leftHit, rightHit;
    bool hitLeft = left->Intersect(ray, tMin, tMax, leftHit);
    bool hitRight = right->Intersect(ray, tMin, tMax, rightHit);

    if (hitLeft && hitRight) {
        // Choose the closer hit point
        if (leftHit.time < rightHit.time) {
            hitRecord = leftHit;
        } else {
            hitRecord = rightHit;
        }
        return true;
    } else if (hitLeft) {
        hitRecord = leftHit;
        return true;
    } else if (hitRight) {
        hitRecord = rightHit;
        return true;
    }

    return false;
}
