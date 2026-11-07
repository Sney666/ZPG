// ==========================================================================
// Author: Vojtěch Špalt (SPA0202)
// ==========================================================================

#include "Scene.h"

Scene::Scene()
    : light(nullptr), fireflyTransform(nullptr), skybox(nullptr), backgroundColor(0.0f, 0.0f, 0.0f) {
}

Scene::~Scene() {
    for (DrawableObject* o : objects) {
        delete o;
    }
    if (light) delete light;
    if (skybox) delete skybox;
}

void Scene::addObject(DrawableObject* object) {
    objects.push_back(object);
}

void Scene::updateClock(ShaderProgram* clockShader) {
    time_t now = time(0);
    tm localTime;
    localtime_s(&localTime, &now);

    float seconds = (float)localTime.tm_sec;
    float minutes = (float)localTime.tm_min + seconds / 60.0f;
    float hours = (float)(localTime.tm_hour % 12) + minutes / 60.0f;

    float twoPi = -6.2831853f;
    clockShader->use();
    clockShader->setUniform("secAngle", (seconds / 60.0f) * twoPi);
    clockShader->setUniform("minAngle", (minutes / 60.0f) * twoPi);
    clockShader->setUniform("hourAngle", (hours / 12.0f) * twoPi);
}

void Scene::updateFirefly() {
    if (light && fireflyTransform) {
        float t = (float)glfwGetTime();
        vec3 newPos(
            sin(t * 0.7f) * 2.5f,
            0.6f + sin(t * 2.2f) * 0.25f,
            cos(t * 0.5f) * 2.5f
        );
        light->setPosition(newPos);
        fireflyTransform->setPosition(newPos);
    }
}

void Scene::render(ShaderProgramFactory* shaders, const vec3& cameraPos) {
    updateFirefly();

    if (skybox != nullptr) {
        glDepthMask(GL_FALSE);
        skybox->render();
        glDepthMask(GL_TRUE);
    }

    if (light) {
        ShaderProgram* litShaders[] = {
            shaders->getAmbientShader(),
            shaders->getDiffuseShader(),
            shaders->getPhongShader(),
            shaders->getBlinnPhongShader()
        };
        for (ShaderProgram* s : litShaders) {
            s->use();
            light->apply(s);
            s->setUniform("viewPosition", cameraPos);
        }
    }

    for (DrawableObject* o : objects) {
        o->render();
    }
}