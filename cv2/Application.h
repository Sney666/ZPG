#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Application {
private:
    GLFWwindow* window;

    GLuint VBO_sphere, VAO_sphere;
    GLuint VBO_square, VAO_square;

    GLuint shaderProgramSphere, shaderProgramSquare;

    GLuint createShaderFromFile(GLenum shaderType, const char* shaderFile);

public:
    Application();
    ~Application();

    void initialization();
    void createShaders();
    void createModels();
    void run();
};