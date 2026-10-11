#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderProgram.h"
#include "Scene.h"

#include "login.h"
#include "bushes.h"
#include "tree.h"
#include "sun.h"
#include "earth.h"
#include "moon.h"

using namespace glm;
using namespace std;

class Application {
private:
    GLFWwindow* window;

    ShaderProgram* basicShader;
    ShaderProgram* lightShader;

    vector<Scene*> scenes;
    int currentScene;

public:
    Application();
    ~Application();

    void initialization();
    void createShaders();
    void createModels();
    void run();
};