#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {
    for (DrawableObject* o : objects) {
        delete o;
    }
}

void Scene::addObject(DrawableObject* object) {
    objects.push_back(object);
}

void Scene::render() {
    for (DrawableObject* o : objects) {
        o->render();
    }
}