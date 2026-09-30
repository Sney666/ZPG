#include "Application.h"
#include "sphere.h"

Application::Application() : window(nullptr), VBO_sphere(0), VAO_sphere(0), VBO_square(0), VAO_square(0), shaderProgramSphere(0), shaderProgramSquare(0) {}

Application::~Application() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void Application::initialization() {
    if (!glfwInit()) exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::cout << "GLAD initialization failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);
}

GLuint Application::createShaderFromFile(GLenum shaderType, const char* shaderFile) {
    GLuint shaderID = glCreateShader(shaderType);
    if (shaderID == 0) { std::cout << "Unable to create shader" << std::endl; exit(EXIT_FAILURE); }

    std::ifstream file(shaderFile);
    if (!file.is_open()) {
        std::cout << "Unable to open file " << shaderFile << std::endl;
        glDeleteShader(shaderID);
        exit(-1);
    }
    std::string shaderCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    const char* source = shaderCode.c_str();
    glShaderSource(shaderID, 1, &source, nullptr);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(shaderID, sizeof(infoLog), nullptr, infoLog);
        std::cout << "Shader failed:\n" << infoLog << std::endl;
        glDeleteShader(shaderID);
        exit(1);
    }
    return shaderID;
}

void Application::createShaders() {
    GLuint vertexShader = createShaderFromFile(GL_VERTEX_SHADER, "basic.vert");
    GLuint fragmentBasic = createShaderFromFile(GL_FRAGMENT_SHADER, "basic.frag");
    GLuint fragmentYellow = createShaderFromFile(GL_FRAGMENT_SHADER, "yellow.frag");

    shaderProgramSphere = glCreateProgram();
    glAttachShader(shaderProgramSphere, fragmentBasic);
    glAttachShader(shaderProgramSphere, vertexShader);
    glLinkProgram(shaderProgramSphere);

    shaderProgramSquare = glCreateProgram();
    glAttachShader(shaderProgramSquare, fragmentYellow);
    glAttachShader(shaderProgramSquare, vertexShader);
    glLinkProgram(shaderProgramSquare);
}

void Application::createModels() {
    float squarePoints[] = {
        -0.6f,  1.0f, -0.5f,   1.0f, 1.0f, 0.0f,
        -0.6f,  0.6f, -0.5f,   1.0f, 1.0f, 0.0f,
        -1.0f,  1.0f, -0.5f,   1.0f, 1.0f, 0.0f,
        -0.6f,  0.6f, -0.5f,   1.0f, 1.0f, 0.0f,
        -1.0f,  0.6f, -0.5f,   1.0f, 1.0f, 0.0f,
        -1.0f,  1.0f, -0.5f,   1.0f, 1.0f, 0.0f
    };

    glGenBuffers(1, &VBO_square);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_square);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squarePoints), squarePoints, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO_square);
    glBindVertexArray(VAO_square);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_square);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

    glGenBuffers(1, &VBO_sphere);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_sphere);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sphere), sphere, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO_sphere);
    glBindVertexArray(VAO_sphere);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_sphere);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
}

void Application::run() {
    int sphereVertexCount = sizeof(sphere) / (6 * sizeof(float));

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgramSphere);
        glBindVertexArray(VAO_sphere);
        glDrawArrays(GL_TRIANGLES, 0, sphereVertexCount);

        glUseProgram(shaderProgramSquare);
        glBindVertexArray(VAO_square);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}