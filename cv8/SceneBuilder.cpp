// ==========================================================================
// Author: Vojtěch Špalt (SPA0202)
// ==========================================================================

#include "SceneBuilder.h"

Scene* SceneBuilder::createForestScene(ModelManager* models, ShaderProgramFactory* shaders) {
    Scene* scene1 = new Scene();
    scene1->setBackgroundColor(vec3(0.5f, 0.7f, 1.0f));

    // Plain
    TransformComposite* plainComp = new TransformComposite();
    plainComp->addTransformation(new Scale(vec3(10.0f, 1.0f, 10.0f)));

    DrawableObject* plainObj = new DrawableObject(models->getPlain(), shaders->getBasicShader(), new Material(0.03f, 0.9f, 0.1f, 8.0f));
    plainObj->setTransformation(plainComp);
    plainObj->setColor(vec3(0.2f, 0.35f, 0.1f), 0);
    scene1->addObject(plainObj);

    // Trees
    for (int i = 0; i < 100; i++) {
        float treeX = (rand() % 1200 - 600) / 100.0f;
        float treeZ = (rand() % 1200 - 600) / 100.0f;
        float treeRot = radians((float)(rand() % 360));
        float treeScale = 0.12f + (rand() % 100) / 1000.0f;

        TransformComposite* treeComp = new TransformComposite();
        treeComp->addTransformation(new Translate(vec3(treeX, 0.0f, treeZ)));
        treeComp->addTransformation(new Rotate(treeRot, vec3(0.0f, 1.0f, 0.0f)));
        treeComp->addTransformation(new Scale(vec3(treeScale)));

        float greenShade = 0.35f + (rand() % 55) / 100.0f;
        float redTint = (rand() % 20) / 100.0f;

        DrawableObject* treeObj = new DrawableObject(models->getTree(), shaders->getTreeShader(), new Material(0.03f, 0.85f, 0.2f, 16.0f));
        treeObj->setTransformation(treeComp);
        treeObj->setColor(vec3(redTint, greenShade, 0.05f), 1);
        scene1->addObject(treeObj);
    }

    // Bushes
    for (int i = 0; i < 200; i++) {
        float bushX = (rand() % 1200 - 600) / 100.0f;
        float bushZ = (rand() % 1200 - 600) / 100.0f;
        float bushRot = radians((float)(rand() % 360));
        float bushScale = 0.5f + (rand() % 40) / 100.0f;

        TransformComposite* bushComp = new TransformComposite();
        bushComp->addTransformation(new Translate(vec3(bushX, 0.0f, bushZ)));
        bushComp->addTransformation(new Rotate(bushRot, vec3(0.0f, 1.0f, 0.0f)));
        bushComp->addTransformation(new Scale(vec3(bushScale)));

        float bushGreen = 0.3f + (rand() % 40) / 100.0f;

        DrawableObject* bushObj = new DrawableObject(models->getBush(), shaders->getTreeShader(), new Material(0.03f, 0.8f, 0.15f, 8.0f));
        bushObj->setTransformation(bushComp);
        bushObj->setColor(vec3(0.1f, bushGreen, 0.1f), 2);
        scene1->addObject(bushObj);
    }

    // Clocks
    TransformComposite* clock1Comp = new TransformComposite();
    clock1Comp->addTransformation(new Translate(vec3(-1.0f, 0.8f, 1.0f)));
    clock1Comp->addTransformation(new Scale(vec3(-0.3f, 0.3f, 0.3f)));

    DrawableObject* clock1 = new DrawableObject(models->getClock(), shaders->getClockShader());
    clock1->setTransformation(clock1Comp);
    scene1->addObject(clock1);

    TransformComposite* clock2Comp = new TransformComposite();
    clock2Comp->addTransformation(new Translate(vec3(2.5f, 1.2f, -2.0f)));
    clock2Comp->addTransformation(new Scale(vec3(-0.3f, 0.3f, 0.3f)));

    DrawableObject* clock2 = new DrawableObject(models->getClock(), shaders->getClockShader());
    clock2->setTransformation(clock2Comp);
    scene1->addObject(clock2);
    
    // Login
    TransformComposite* loginComp = new TransformComposite();
    loginComp->addTransformation(new Translate(vec3(0.0f, 2.5f, -3.0f)));
    DrawableObject* loginObj = new DrawableObject(models->getLogin(), shaders->getBasicShader());
    loginObj->setTransformation(loginComp);
    loginObj->setColor(vec3(1.0f), -1);
    scene1->addObject(loginObj);

    return scene1;
}

Scene* SceneBuilder::createSolarSystemScene(ModelManager* models, ShaderProgramFactory* shaders) {
    Scene* scene2 = new Scene();
    scene2->setLight(new Light(vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f));

    // Sun
    TransformComposite* sunComp = new TransformComposite();
    sunComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 0.0f), 0.3f));
    sunComp->addTransformation(new Scale(vec3(0.4f)));
    DrawableObject* sunObj = new DrawableObject(models->getSun(), shaders->getAmbientShader(), new Material(1.0f, 0.0f, 0.0f, 1.0f));
    sunObj->setTransformation(sunComp);
    sunObj->setColor(vec3(1.0f), -1);
    scene2->addObject(sunObj);

    // Earth
    TransformComposite* earthComp = new TransformComposite();
    earthComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 0.0f), 0.5f));
    earthComp->addTransformation(new Translate(vec3(0.8f, 0.0f, 0.0f)));
    earthComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 0.0f), 0.7f));
    earthComp->addTransformation(new Scale(vec3(0.15f)));
    DrawableObject* earthObj = new DrawableObject(models->getEarth(), shaders->getBlinnPhongShader(), new Material(0.1f, 1.0f, 0.5f, 32.0f));
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
    DrawableObject* moonObj = new DrawableObject(models->getMoon(), shaders->getBlinnPhongShader(), new Material(0.1f, 1.0f, 0.3f, 16.0f));
    moonObj->setTransformation(moonComp);
    moonObj->setColor(vec3(1.0f), -1);
    scene2->addObject(moonObj);

    // Rocket
    TransformComposite* rocketComp = new TransformComposite();
    rocketComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 1.0f), 0.6f));
    rocketComp->addTransformation(new Translate(vec3(1.1f, 0.0f, 0.0f)));
    rocketComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 1.0f), 0.6f));
    rocketComp->addTransformation(new Scale(vec3(0.10f)));
    DrawableObject* rocketObj = new DrawableObject(models->getRocket(), shaders->getPhongShader(), new Material(0.1f, 1.0f, 0.8f, 64.0f));
    rocketObj->setTransformation(rocketComp);
    rocketObj->setColor(vec3(1.0f), -1);
    scene2->addObject(rocketObj);

    // Login
    TransformComposite* loginComp = new TransformComposite();
    loginComp->addTransformation(new Translate(vec3(0.0f, 1.5f, -2.0f)));
    loginComp->addTransformation(new Scale(vec3(0.5f)));
    DrawableObject* loginObj = new DrawableObject(models->getLogin(), shaders->getBasicShader());
    loginObj->setTransformation(loginComp);
    loginObj->setColor(vec3(1.0f), -1);
    scene2->addObject(loginObj);

    return scene2;
}

Scene* SceneBuilder::createSpheresScene(ModelManager* models, ShaderProgramFactory* shaders) {
    Scene* scene3 = new Scene();
    scene3->setLight(new Light(vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.0f, 0.0f));

    // Ambient
    TransformComposite* sphere1Comp = new TransformComposite();
    sphere1Comp->addTransformation(new Translate(vec3(0.0f, 2.0f, 0.0f)));
    DrawableObject* sphere1Obj = new DrawableObject(models->getSphere(), shaders->getAmbientShader(), new Material(0.2f, 0.0f, 0.0f, 1.0f));
    sphere1Obj->setTransformation(sphere1Comp);
    sphere1Obj->setColor(vec3(0.2f, 0.5f, 0.8f), 0);
    scene3->addObject(sphere1Obj);

    // Diffuse
    TransformComposite* sphere2Comp = new TransformComposite();
    sphere2Comp->addTransformation(new Translate(vec3(0.0f, -2.0f, 0.0f)));
    DrawableObject* sphere2Obj = new DrawableObject(models->getSphere(), shaders->getDiffuseShader(), new Material(0.1f, 1.0f, 0.0f, 1.0f));
    sphere2Obj->setTransformation(sphere2Comp);
    sphere2Obj->setColor(vec3(0.2f, 0.5f, 0.8f), 0);
    scene3->addObject(sphere2Obj);

    // Phong
    TransformComposite* sphere3Comp = new TransformComposite();
    sphere3Comp->addTransformation(new Translate(vec3(-2.0f, 0.0f, 0.0f)));
    DrawableObject* sphere3Obj = new DrawableObject(models->getSphere(), shaders->getPhongShader(), new Material(0.1f, 1.0f, 0.5f, 32.0f));
    sphere3Obj->setTransformation(sphere3Comp);
    sphere3Obj->setColor(vec3(0.2f, 0.5f, 0.8f), 0);
    scene3->addObject(sphere3Obj);

    // Blinn-Phong
    TransformComposite* sphere4Comp = new TransformComposite();
    sphere4Comp->addTransformation(new Translate(vec3(2.0f, 0.0f, 0.0f)));
    DrawableObject* sphere4Obj = new DrawableObject(models->getSphere(), shaders->getBlinnPhongShader(), new Material(0.1f, 1.0f, 0.5f, 64.0f));
    sphere4Obj->setTransformation(sphere4Comp);
    sphere4Obj->setColor(vec3(0.2f, 0.5f, 0.8f), 0);
    scene3->addObject(sphere4Obj);

    // Login
    TransformComposite* loginComp = new TransformComposite();
    loginComp->addTransformation(new Translate(vec3(0.0f, 0.0f, -3.0f)));
    loginComp->addTransformation(new Scale(vec3(0.5f)));
    DrawableObject* loginObj = new DrawableObject(models->getLogin(), shaders->getBasicShader());
    loginObj->setTransformation(loginComp);
    loginObj->setColor(vec3(1.0f), -1);
    scene3->addObject(loginObj);

    return scene3;
}

Scene* SceneBuilder::createNightForestScene(ModelManager* models, ShaderProgramFactory* shaders) {
    Scene* scene4 = new Scene();
    scene4->setBackgroundColor(vec3(0.02f, 0.03f, 0.12f));

    // Firefly
    vec3 fireflyColor(0.75f, 1.0f, 0.2f);
    Light* fireflyLight = new Light(vec3(0.0f, 0.6f, 0.0f), fireflyColor, 1.0f, 0.5f, 1.2f);
    scene4->setLight(fireflyLight);

    Translate* fireflyPosTrans = new Translate(vec3(0.0f, 0.6f, 0.0f));
    TransformComposite* fireflyComp = new TransformComposite();
    fireflyComp->addTransformation(fireflyPosTrans);
    fireflyComp->addTransformation(new Scale(vec3(0.02f)));

    DrawableObject* fireflyBody = new DrawableObject(models->getSphere(), shaders->getAmbientShader(), new Material(1.0f, 0.0f, 0.0f, 1.0f));
    fireflyBody->setTransformation(fireflyComp);
    fireflyBody->setColor(fireflyColor, 0);
    scene4->addObject(fireflyBody);
    scene4->setFireflyTransform(fireflyPosTrans);

    // Plain
    TransformComposite* plainComp = new TransformComposite();
    plainComp->addTransformation(new Scale(vec3(10.0f, 1.0f, 10.0f)));
    DrawableObject* plainObj = new DrawableObject(models->getPlain(), shaders->getPhongShader(), new Material(0.03f, 0.9f, 0.1f, 8.0f));
    plainObj->setTransformation(plainComp);
    plainObj->setColor(vec3(0.2f, 0.35f, 0.1f), 0);
    scene4->addObject(plainObj);

    // Trees
    for (int i = 0; i < 100; i++) {
        float treeX = (rand() % 1200 - 600) / 100.0f;
        float treeZ = (rand() % 1200 - 600) / 100.0f;
        float treeRot = radians((float)(rand() % 360));
        float treeScale = 0.12f + (rand() % 100) / 1000.0f;

        TransformComposite* treeComp = new TransformComposite();
        treeComp->addTransformation(new Translate(vec3(treeX, 0.0f, treeZ)));
        treeComp->addTransformation(new Rotate(treeRot, vec3(0.0f, 1.0f, 0.0f)));
        treeComp->addTransformation(new Scale(vec3(treeScale)));

        float greenShade = 0.35f + (rand() % 55) / 100.0f;
        float redTint = (rand() % 20) / 100.0f;

        DrawableObject* treeObj = new DrawableObject(models->getTree(), shaders->getPhongShader(), new Material(0.03f, 0.85f, 0.2f, 16.0f));
        treeObj->setTransformation(treeComp);
        treeObj->setColor(vec3(redTint, greenShade, 0.05f), 1);
        scene4->addObject(treeObj);
    }

    // Bushes
    for (int i = 0; i < 200; i++) {
        float bushX = (rand() % 1200 - 600) / 100.0f;
        float bushZ = (rand() % 1200 - 600) / 100.0f;
        float bushRot = radians((float)(rand() % 360));
        float bushScale = 0.5f + (rand() % 40) / 100.0f;

        TransformComposite* bushComp = new TransformComposite();
        bushComp->addTransformation(new Translate(vec3(bushX, 0.0f, bushZ)));
        bushComp->addTransformation(new Rotate(bushRot, vec3(0.0f, 1.0f, 0.0f)));
        bushComp->addTransformation(new Scale(vec3(bushScale)));

        float bushGreen = 0.3f + (rand() % 40) / 100.0f;

        DrawableObject* bushObj = new DrawableObject(models->getBush(), shaders->getPhongShader(), new Material(0.03f, 0.8f, 0.15f, 8.0f));
        bushObj->setTransformation(bushComp);
        bushObj->setColor(vec3(0.1f, bushGreen, 0.1f), 2);
        scene4->addObject(bushObj);
    }

    // Login
    TransformComposite* loginComp = new TransformComposite();
    loginComp->addTransformation(new Translate(vec3(0.0f, 2.5f, -3.0f)));
    DrawableObject* loginObj = new DrawableObject(models->getLogin(), shaders->getBasicShader());
    loginObj->setTransformation(loginComp);
    loginObj->setColor(vec3(1.0f), -1);
    scene4->addObject(loginObj);

    return scene4;
}

Scene* SceneBuilder::createEB408Scene(ModelManager* models, ShaderProgramFactory* shaders) {
    Scene* scene5 = new Scene();
    scene5->setBackgroundColor(vec3(0.2f, 0.2f, 0.2f));

    // Skybox
    std::vector<std::string> faces = {
        "skybox/posx.jpg",
        "skybox/negx.jpg",
        "skybox/posy.jpg",
        "skybox/negy.jpg",
        "skybox/posz.jpg",
        "skybox/negz.jpg"
    };
    Texture* skyboxTex = new Texture(faces);
    DrawableObject* skyboxObj = new DrawableObject(models->getSkybox(), shaders->getSkyboxShader());
    skyboxObj->setTexture(skyboxTex);
    scene5->setSkybox(skyboxObj);

    // EB408
    Texture* eb408Tex = new Texture("EB408/T_EB408.png");
    TransformComposite* eb408Comp = new TransformComposite();
    eb408Comp->addTransformation(new Rotate(radians(-90.0f), vec3(1.0f, 0.0f, 0.0f)));
    eb408Comp->addTransformation(new Scale(vec3(1.0f)));
    DrawableObject* eb408Obj = new DrawableObject(models->getEb408(), shaders->getTextureShader());
    eb408Obj->setTransformation(eb408Comp);
    eb408Obj->setTexture(eb408Tex);
    scene5->addObject(eb408Obj);

    // Door
    Texture* doorTex = new Texture("door/T_door_basecolor.png");
    TransformComposite* doorComp = new TransformComposite();
    doorComp->addTransformation(new Translate(vec3(-2.4f, 0.0f, 7.7f)));
    doorComp->addTransformation(new Rotate(radians(-90.0f), vec3(1.0f, 0.0f, 0.0f)));
    doorComp->addTransformation(new Scale(vec3(0.01f)));
    DrawableObject* doorObj = new DrawableObject(models->getDoor(), shaders->getTextureShader());
    doorObj->setTransformation(doorComp);
    doorObj->setTexture(doorTex);
    scene5->addObject(doorObj);

    // Whiteboard
    Texture* boardTex = new Texture("whiteboard/whiteboard.png");
    TransformComposite* boardComp = new TransformComposite();
    boardComp->addTransformation(new Translate(vec3(-3.7f, 0.1f, 2.0f)));
    boardComp->addTransformation(new Rotate(radians(-90.0f), vec3(1.0f, 0.0f, 0.0f)));
    boardComp->addTransformation(new Scale(vec3(1.0f)));
    DrawableObject* boardObj = new DrawableObject(models->getWhiteboard(), shaders->getTextureShader());
    boardObj->setTransformation(boardComp);
    boardObj->setTexture(boardTex);
    scene5->addObject(boardObj);

    // Shrek
    Texture* shrekTex = new Texture("shrek/shrek.png");
    TransformComposite* shrekComp = new TransformComposite();
    shrekComp->addTransformation(new Translate(vec3(-3.5f, 0.0f, 4.0f)));
    shrekComp->addTransformation(new Rotate(radians(-90.0f), vec3(0.0f, -1.0f, 0.0f)));
    shrekComp->addTransformation(new Scale(vec3(1.0f)));
    DrawableObject* shrekObj = new DrawableObject(models->getShrek(), shaders->getTextureShader());
    shrekObj->setTransformation(shrekComp);
    shrekObj->setTexture(shrekTex);
    scene5->addObject(shrekObj);

    // Fiona
    Texture* fionaTex = new Texture("shrek/fiona.png");
    TransformComposite* fionaComp = new TransformComposite();
    fionaComp->addTransformation(new Translate(vec3(-3.5f, 0.0f, 6.0f)));
    fionaComp->addTransformation(new Rotate(radians(-90.0f), vec3(0.0f, -1.0f, 0.0f)));
    fionaComp->addTransformation(new Scale(vec3(1.0f)));
    DrawableObject* fionaObj = new DrawableObject(models->getFiona(), shaders->getTextureShader());
    fionaObj->setTransformation(fionaComp);
    fionaObj->setTexture(fionaTex);
    scene5->addObject(fionaObj);

    // Toilet
    Texture* toiletTex = new Texture("shrek/toiled.jpg");
    TransformComposite* toiletComp = new TransformComposite();
    toiletComp->addTransformation(new Translate(vec3(2.5f, 0.0f, 2.5f)));
    toiletComp->addTransformation(new Scale(vec3(0.5f)));
    DrawableObject* toiletObj = new DrawableObject(models->getToilet(), shaders->getTextureShader());
    toiletObj->setTransformation(toiletComp);
    toiletObj->setTexture(toiletTex);
    scene5->addObject(toiletObj);

    // Login
    TransformComposite* loginComp = new TransformComposite();
    loginComp->addTransformation(new Translate(vec3(-3.7f, 2.0f, 5.2f)));
    loginComp->addTransformation(new Rotate(radians(-90.0f), vec3(0.0f, -1.0f, 0.0f)));
    loginComp->addTransformation(new Scale(vec3(0.2f)));
    DrawableObject* loginObj = new DrawableObject(models->getLogin(), shaders->getBasicShader());
    loginObj->setTransformation(loginComp);
    loginObj->setColor(vec3(1.0f), -1);
    scene5->addObject(loginObj);

    return scene5;
}