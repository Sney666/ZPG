// ==========================================================================
// Author: Vojtěch Špalt (SPA0202)
// ==========================================================================

#include "ShaderProgramFactory.h"

ShaderProgramFactory::ShaderProgramFactory() {
    basicShader = new ShaderProgram("shaders/basic.vert", "shaders/basic.frag");
    treeShader = new ShaderProgram("shaders/tree.vert", "shaders/basic.frag");
    clockShader = new ShaderProgram("shaders/clock.vert", "shaders/clock.frag");
    ambientShader = new ShaderProgram("shaders/light.vert", "shaders/ambient.frag");
    diffuseShader = new ShaderProgram("shaders/light.vert", "shaders/diffuse.frag");
    phongShader = new ShaderProgram("shaders/light.vert", "shaders/phong.frag");
    blinnPhongShader = new ShaderProgram("shaders/light.vert", "shaders/blinn.frag");
}

ShaderProgramFactory::~ShaderProgramFactory() {
    delete basicShader;
    delete treeShader;
    delete clockShader;
    delete ambientShader;
    delete diffuseShader;
    delete phongShader;
    delete blinnPhongShader;
}

void ShaderProgramFactory::attachAllToCamera(Camera* camera) {
    if (!camera) return;
    camera->attach(basicShader);
    camera->attach(treeShader);
    camera->attach(clockShader);
    camera->attach(ambientShader);
    camera->attach(diffuseShader);
    camera->attach(phongShader);
    camera->attach(blinnPhongShader);
}

ShaderProgram* ShaderProgramFactory::getBasicShader() { return basicShader; }
ShaderProgram* ShaderProgramFactory::getTreeShader() { return treeShader; }
ShaderProgram* ShaderProgramFactory::getClockShader() { return clockShader; }
ShaderProgram* ShaderProgramFactory::getAmbientShader() { return ambientShader; }
ShaderProgram* ShaderProgramFactory::getDiffuseShader() { return diffuseShader; }
ShaderProgram* ShaderProgramFactory::getPhongShader() { return phongShader; }
ShaderProgram* ShaderProgramFactory::getBlinnPhongShader() { return blinnPhongShader; }