#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {
    for (Model* m : models) {
        delete m;
    }
}

void Scene::addModel(Model* model) {
    models.push_back(model);
}

void Scene::render() {
    for (Model* m : models) {
        m->render();
    }
}