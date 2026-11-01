// ==========================================================================
// Author: Vojtěch Špalt (SPA0202)
// ==========================================================================

#include "Application.h"

Application::Application()
    : window(nullptr), shaderFactory(nullptr), modelManager(nullptr),
    camera(nullptr), currentScene(0), isRightMousePressed(false),
    lastX(0.0), lastY(0.0) {
}

Application::~Application() {
    for (Scene* s : scenes) {
        delete s;
    }
    delete modelManager;
    delete shaderFactory;
    delete camera;

    if (window) glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::onWindowResize(int width, int height) {
    if (height == 0) return;

    //glViewport(0, 0, width, height);
    //return;

    glViewport(0, 0, width, height);
    if (camera) {
        camera->setAspectRatio((float)width / (float)height);
    }
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
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int w, int h) {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(win));
        if (app) {
            app->onWindowResize(w, h);
        }
        });

    srand((unsigned int)time(NULL));
}

void Application::createShaders() {
    shaderFactory = new ShaderProgramFactory();
    camera = new Camera(vec3(0.0f, 0.5f, 3.0f));

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    if (height > 0) {
        camera->setAspectRatio((float)width / (float)height);
    }

    shaderFactory->attachAllToCamera(camera);
}

void Application::createModels() {
    modelManager = new ModelManager();

    scenes.push_back(SceneBuilder::createForestScene(modelManager, shaderFactory));
    scenes.push_back(SceneBuilder::createSolarSystemScene(modelManager, shaderFactory));
    scenes.push_back(SceneBuilder::createSpheresScene(modelManager, shaderFactory));
    scenes.push_back(SceneBuilder::createNightForestScene(modelManager, shaderFactory));
}

void Application::processInput(float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        currentScene = 0;
        camera->setPositionAndAngles(vec3(0.0f, 0.5f, 3.0f), 1.57f, -1.57f);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        currentScene = 1;
        camera->setPositionAndAngles(vec3(0.0f, 1.2f, 2.5f), 2.0f, -1.57f);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        currentScene = 2;
        camera->setPositionAndAngles(vec3(0.0f, 0.0f, 6.0f), 1.57f, -1.57f);
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
        currentScene = 3;
        camera->setPositionAndAngles(vec3(0.0f, 1.0f, 4.0f), 1.75f, -1.57f);
    }

    if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS) camera->setFov(30.0f);
    if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS) camera->setFov(45.0f);
    if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS) camera->setFov(60.0f);
    if (glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS) camera->setFov(90.0f);
    if (glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS) camera->setFov(120.0f);
    if (glfwGetKey(window, GLFW_KEY_F6) == GLFW_PRESS) camera->setFov(150.0f);
    if (glfwGetKey(window, GLFW_KEY_F7) == GLFW_PRESS) camera->setFov(170.0f);

    float moveSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera->moveForward(moveSpeed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera->moveBackward(moveSpeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera->moveLeft(moveSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera->moveRight(moveSpeed);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        double currentX, currentY;
        glfwGetCursorPos(window, &currentX, &currentY);

        if (!isRightMousePressed) {
            lastX = currentX;
            lastY = currentY;
            isRightMousePressed = true;
        }
        else {
            float deltaX = (float)(currentX - lastX);
            float deltaY = (float)(currentY - lastY);

            lastX = currentX;
            lastY = currentY;

            float mouseSensitivity = 0.005f;
            camera->updateAngles(deltaY * mouseSensitivity, deltaX * mouseSensitivity);
        }
    }
    else {
        isRightMousePressed = false;
    }
}

void Application::run() {
    float lastFrameTime = (float)glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        float currentFrameTime = (float)glfwGetTime();
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        processInput(deltaTime);

        if (currentScene >= 0 && currentScene < scenes.size()) {
            vec3 bg = scenes[currentScene]->getBackgroundColor();
            glClearColor(bg.r, bg.g, bg.b, 1.0f);
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (currentScene == 0) {
            scenes[0]->updateClock(shaderFactory->getClockShader());
        }

        if (currentScene >= 0 && currentScene < scenes.size()) {
            scenes[currentScene]->render(shaderFactory, camera->getPosition());
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}