#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderProgram.h"
#include "login.h"
#include "Scene.h"
#include "sphere.h"
#include "bushes.h"
#include "tree.h"

using namespace std;

class Application {
private:
    GLFWwindow* window;

    ShaderProgram* myShader;

    std::vector<Scene*> scenes;
    int currentScene;

public:
    Application();
    ~Application();

    void initialization();
    void createShaders();
    void createModels();
    void run();
};