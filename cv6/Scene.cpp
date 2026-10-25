// ==========================================================================
// Author: Vojtěch Špalt (SPA0202)
// ==========================================================================

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

void Scene::updateClock(ShaderProgram* clockShader) {
    time_t now = time(0);
    tm localTime;
    localtime_s(&localTime, &now);

    float seconds = (float)localTime.tm_sec;
    float minutes = (float)localTime.tm_min + seconds / 60.0f;
    float hours = (float)(localTime.tm_hour % 12) + minutes / 60.0f;

    float twoPi = -6.2831853f;
    float secAngle = (seconds / 60.0f) * twoPi;
    float minAngle = (minutes / 60.0f) * twoPi;
    float hourAngle = (hours / 12.0f) * twoPi;

    clockShader->use();
    clockShader->setUniform("secAngle", secAngle);
    clockShader->setUniform("minAngle", minAngle);
    clockShader->setUniform("hourAngle", hourAngle);
}

Scene* Scene::createForestScene(Model* plainModel, Model* treeModel, Model* bushModel, Model* clockModelReal, Model* loginModel, ShaderProgram* basicShader, ShaderProgram* clockShader, ShaderProgram* treeShader) {
    // First scene
    Scene* scene1 = new Scene();

    // Plain
    TransformComposite* plainComp = new TransformComposite();
    plainComp->addTransformation(new Scale(vec3(15.0f, 1.0f, 15.0f)));

    DrawableObject* plainObj = new DrawableObject(plainModel, basicShader);
    plainObj->setTransformation(plainComp);
    plainObj->setColor(vec3(0.2f, 0.35f, 0.1f), 0);
    scene1->addObject(plainObj);

    // Trees
    for (int i = 0; i < 100; i++) {
        float treeX = (rand() % 1400 - 700) / 100.0f;
        float treeZ = (rand() % 1400 - 700) / 100.0f;
        float treeRot = radians((float)(rand() % 360));
        float treeScale = 0.12f + (rand() % 100) / 1000.0f;

        TransformComposite* treeComp = new TransformComposite();
        treeComp->addTransformation(new Translate(vec3(treeX, 0.0f, treeZ)));
        treeComp->addTransformation(new Rotate(treeRot, vec3(0.0f, 1.0f, 0.0f)));
        treeComp->addTransformation(new Scale(vec3(treeScale)));

        float greenShade = 0.35f + (rand() % 55) / 100.0f;
        float redTint = (rand() % 20) / 100.0f;

        DrawableObject* treeObj = new DrawableObject(treeModel, treeShader);
        treeObj->setTransformation(treeComp);
        treeObj->setColor(vec3(redTint, greenShade, 0.05f), 1);
        scene1->addObject(treeObj);
    }

    // Bushes
    for (int i = 0; i < 200; i++) {
        float bushX = (rand() % 1400 - 700) / 100.0f;
        float bushZ = (rand() % 1400 - 700) / 100.0f;
        float bushRot = radians((float)(rand() % 360));
        float bushScale = 0.5f + (rand() % 40) / 100.0f;

        TransformComposite* bushComp = new TransformComposite();
        bushComp->addTransformation(new Translate(vec3(bushX, 0.0f, bushZ)));
        bushComp->addTransformation(new Rotate(bushRot, vec3(0.0f, 1.0f, 0.0f)));
        bushComp->addTransformation(new Scale(vec3(bushScale)));

        float bushGreen = 0.3f + (rand() % 40) / 100.0f;

        DrawableObject* bushObj = new DrawableObject(bushModel, treeShader);
        bushObj->setTransformation(bushComp);
        bushObj->setColor(vec3(0.1f, bushGreen, 0.1f), 2);
        scene1->addObject(bushObj);
    }

    // Clocks
    TransformComposite* clock1Comp = new TransformComposite();
    clock1Comp->addTransformation(new Translate(vec3(-1.0f, 0.8f, 1.0f)));
    clock1Comp->addTransformation(new Scale(vec3(-0.3f, 0.3f, 0.3f)));

    DrawableObject* clock1 = new DrawableObject(clockModelReal, clockShader);
    clock1->setTransformation(clock1Comp);
    scene1->addObject(clock1);

    TransformComposite* clock2Comp = new TransformComposite();
    clock2Comp->addTransformation(new Translate(vec3(2.5f, 1.2f, -2.0f)));
    clock2Comp->addTransformation(new Scale(vec3(-0.3, 0.3f, 0.3f)));

    DrawableObject* clock2 = new DrawableObject(clockModelReal, clockShader);
    clock2->setTransformation(clock2Comp);
    scene1->addObject(clock2);

    // Login
    TransformComposite* loginComp = new TransformComposite();
    loginComp->addTransformation(new Translate(vec3(0.0f, 2.5f, -3.0f)));

    DrawableObject* loginObj = new DrawableObject(loginModel, basicShader);
    loginObj->setTransformation(loginComp);
    loginObj->setColor(vec3(1.0f), -1);
    scene1->addObject(loginObj);

    return scene1;
}

Scene* Scene::createSolarSystemScene(Model* sunModel, Model* earthModel, Model* moonModel, Model* rocketModel, Model* loginModel, ShaderProgram* ambientShader, ShaderProgram* phongShader, ShaderProgram* blinnPhongShader, ShaderProgram* basicShader) {
    // Second scene
    Scene* scene2 = new Scene();

    // Sun
    TransformComposite* sunComp = new TransformComposite();
    sunComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 0.0f), 0.3f));
    sunComp->addTransformation(new Scale(vec3(0.4f)));

    DrawableObject* sunObj = new DrawableObject(sunModel, ambientShader);
    sunObj->setTransformation(sunComp);
    sunObj->setColor(vec3(1.0f), -1);
    scene2->addObject(sunObj);

    // Earth
    TransformComposite* earthComp = new TransformComposite();
    earthComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 0.0f), 0.5f));
    earthComp->addTransformation(new Translate(vec3(0.8f, 0.0f, 0.0f)));
    earthComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 0.0f), 0.7f));
    earthComp->addTransformation(new Scale(vec3(0.15f)));

    DrawableObject* earthObj = new DrawableObject(earthModel, blinnPhongShader);
    earthObj->setTransformation(earthComp);
    earthObj->setColor(vec3(1.0f), -1);
    scene2->addObject(earthObj);

    // Moon
    TransformComposite* moonComp = new TransformComposite();
    moonComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 0.0f), 0.5f));
    moonComp->addTransformation(new Translate(vec3(0.8f, 0.0f, 0.0f)));
    moonComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 0.0f), 1.0f));
    moonComp->addTransformation(new Translate(vec3(0.3f, 0.0f, 0.0f)));
    moonComp->addTransformation(new Scale(vec3(0.05f)));

    DrawableObject* moonObj = new DrawableObject(moonModel, blinnPhongShader);
    moonObj->setTransformation(moonComp);
    moonObj->setColor(vec3(1.0f), -1);
    scene2->addObject(moonObj);

    // Rocket
    TransformComposite* rocketComp = new TransformComposite();
    rocketComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 1.0f), 0.6f));
    rocketComp->addTransformation(new Translate(vec3(1.1f, 0.0f, 0.0f)));
    rocketComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 1.0f), 0.6f));
    rocketComp->addTransformation(new Scale(vec3(0.10f)));

    DrawableObject* rocketObj = new DrawableObject(rocketModel, phongShader);
    rocketObj->setTransformation(rocketComp);
    rocketObj->setColor(vec3(1.0f), -1);
    scene2->addObject(rocketObj);

    // Login 
    TransformComposite* loginComp = new TransformComposite();
    loginComp->addTransformation(new Translate(vec3(0.0f, 1.5f, -2.0f)));
    loginComp->addTransformation(new Scale(vec3(0.5f)));
    DrawableObject* loginObj = new DrawableObject(loginModel, basicShader);
    loginObj->setTransformation(loginComp);
    loginObj->setColor(vec3(1.0f), -1);
    scene2->addObject(loginObj);

    return scene2;
}

Scene* Scene::createSpheresScene(Model* sphereModel, Model* loginModel, ShaderProgram* ambientShader, ShaderProgram* diffuseShader, ShaderProgram* phongShader, ShaderProgram* blinnPhongShader, ShaderProgram* basicShader) {
    // Third scene
    Scene* scene3 = new Scene();

    TransformComposite* sphere1Comp = new TransformComposite();
    sphere1Comp->addTransformation(new Translate(vec3(0.0f, 2.0f, 0.0f)));
    DrawableObject* sphere1Obj = new DrawableObject(sphereModel, ambientShader);
    sphere1Obj->setTransformation(sphere1Comp);
    sphere1Obj->setColor(vec3(0.2f, 0.5f, 0.8f), 0);
    scene3->addObject(sphere1Obj);

    TransformComposite* sphere2Comp = new TransformComposite();
    sphere2Comp->addTransformation(new Translate(vec3(0.0f, -2.0f, 0.0f)));
    DrawableObject* sphere2Obj = new DrawableObject(sphereModel, diffuseShader);
    sphere2Obj->setTransformation(sphere2Comp);
    sphere2Obj->setColor(vec3(0.2f, 0.5f, 0.8f), 0);
    scene3->addObject(sphere2Obj);

    TransformComposite* sphere3Comp = new TransformComposite();
    sphere3Comp->addTransformation(new Translate(vec3(-2.0f, 0.0f, 0.0f)));
    DrawableObject* sphere3Obj = new DrawableObject(sphereModel, phongShader);
    sphere3Obj->setTransformation(sphere3Comp);
    sphere3Obj->setColor(vec3(0.2f, 0.5f, 0.8f), 0);
    scene3->addObject(sphere3Obj);

    TransformComposite* sphere4Comp = new TransformComposite();
    sphere4Comp->addTransformation(new Translate(vec3(2.0f, 0.0f, 0.0f)));
    DrawableObject* sphere4Obj = new DrawableObject(sphereModel, blinnPhongShader);
    sphere4Obj->setTransformation(sphere4Comp);
    sphere4Obj->setColor(vec3(0.2f, 0.5f, 0.8f), 0);
    scene3->addObject(sphere4Obj);

    // Login 
    TransformComposite* loginComp = new TransformComposite();
    loginComp->addTransformation(new Translate(vec3(0.0f, 0.0f, -3.0f)));
    loginComp->addTransformation(new Scale(vec3(0.5f)));
    DrawableObject* loginObj = new DrawableObject(loginModel, basicShader);
    loginObj->setTransformation(loginComp);
    loginObj->setColor(vec3(1.0f), -1);
    scene3->addObject(loginObj);

    return scene3;
}