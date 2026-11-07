// ==========================================================================
// Author: Vojtěch Špalt (SPA0202)
// ==========================================================================

#include "ModelManager.h"

ModelManager::ModelManager() {
    treeModel = new Model((float*)tree, sizeof(tree) / sizeof(float), 6);
    bushModel = new Model((float*)bushes, sizeof(bushes) / sizeof(float), 6);
    plainModel = new Model((float*)plain, sizeof(plain) / sizeof(float), 6);
    clockModelReal = new Model((float*)clockModel, sizeof(clockModel) / sizeof(float), 9);

    sunModel = new Model((float*)sun, sizeof(sun) / sizeof(float), 9);
    earthModel = new Model((float*)earth, sizeof(earth) / sizeof(float), 9);
    moonModel = new Model((float*)moon, sizeof(moon) / sizeof(float), 9);
    rocketModel = new Model((float*)rocket, sizeof(rocket) / sizeof(float), 9);

    sphereModel = new Model((float*)sphere, sizeof(sphere) / sizeof(float), 6);

    vector<float> loginData = generateLoginModel();
    loginModel = new Model(loginData.data(), (int)loginData.size(), 6);

    skyboxModel = new Model((float*)skybox, sizeof(skybox) / sizeof(float), 8);
    shrekModel = new Model((float*)shrek, sizeof(shrek) / sizeof(float), 8);
    fionaModel = new Model((float*)fiona, sizeof(fiona) / sizeof(float), 8);
    toiletModel = new Model((float*)toilet, sizeof(toilet) / sizeof(float), 8);
    eb408Model = new Model((float*)eb408, sizeof(eb408) / sizeof(float), 8);
    doorModel = new Model((float*)door, sizeof(door) / sizeof(float), 8);
    whiteboardModel = new Model((float*)whiteboard, sizeof(whiteboard) / sizeof(float), 8);
}

ModelManager::~ModelManager() {
    delete treeModel;
    delete bushModel;
    delete plainModel;
    delete clockModelReal;

    delete sunModel;
    delete earthModel;
    delete moonModel;
    delete rocketModel;

    delete sphereModel;

    delete loginModel;

    delete skyboxModel;
    delete shrekModel;
    delete fionaModel;
    delete toiletModel;
    delete eb408Model;
    delete doorModel;
    delete whiteboardModel;
}

Model* ModelManager::getTree() { return treeModel; }
Model* ModelManager::getBush() { return bushModel; }
Model* ModelManager::getPlain() { return plainModel; }
Model* ModelManager::getClock() { return clockModelReal; }

Model* ModelManager::getSun() { return sunModel; }
Model* ModelManager::getEarth() { return earthModel; }
Model* ModelManager::getMoon() { return moonModel; }
Model* ModelManager::getRocket() { return rocketModel; }

Model* ModelManager::getSphere() { return sphereModel; }

Model* ModelManager::getLogin() { return loginModel; }

Model* ModelManager::getSkybox() { return skyboxModel; }
Model* ModelManager::getShrek() { return shrekModel; }
Model* ModelManager::getFiona() { return fionaModel; }
Model* ModelManager::getToilet() { return toiletModel; }
Model* ModelManager::getEb408() { return eb408Model; }
Model* ModelManager::getDoor() { return doorModel; }
Model* ModelManager::getWhiteboard() { return whiteboardModel; }