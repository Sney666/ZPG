#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <ctime>

#include "ShaderProgram.h"
#include "Scene.h"
#include "Camera.h"

#include "login.h"
#include "bushes.h"
#include "tree.h"
#include "sun.h"
#include "earth.h"
#include "moon.h"
#include "clock.h"
#include "plain.h"

using namespace glm;
using namespace std;

class Application {
private:
    GLFWwindow* window;

    ShaderProgram* basicShader;
    ShaderProgram* clockShader;

    Camera* camera;

    vector<Model*> models;
    vector<Scene*> scenes;
    int currentScene;

    double lastX = 400.0;
    double lastY = 300.0;
    bool isRightMousePressed = false;

public:
    Application();
    ~Application();

    void initialization();
    void createShaders();
    void createModels();

    void processInput(float deltaTime);
    void updateClock();
    void run();
};