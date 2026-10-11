#pragma once
#include <vector>
#include "DrawableObject.h"

class Scene {
private:
    std::vector<DrawableObject*> objects;

public:
    Scene();
    ~Scene();

    void addObject(DrawableObject* object);
    void render();
    std::vector<DrawableObject*>& getObjects() { return objects; }
};