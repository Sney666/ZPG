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