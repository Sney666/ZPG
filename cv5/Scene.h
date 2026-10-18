#pragma once
#include <vector>
#include "DrawableObject.h"

using namespace std;

class Scene {
private:
    std::vector<DrawableObject*> objects;

public:
    Scene();
    ~Scene();

    void addObject(DrawableObject* object);
    void render();
    vector<DrawableObject*>& getObjects() { return objects; }
};