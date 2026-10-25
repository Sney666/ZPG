// ==========================================================================
// Author: Vojtěch Špalt (SPA0202)
// ==========================================================================

#include "Application.h"

Application::Application()
    : window(nullptr), basicShader(nullptr), treeShader(nullptr), clockShader(nullptr),
    ambientShader(nullptr), diffuseShader(nullptr), phongShader(nullptr),
    blinnPhongShader(nullptr), camera(nullptr), currentScene(0),
    isRightMousePressed(false), lastX(0.0), lastY(0.0) {
}

Application::~Application() {
    for (Scene* s : scenes) {
        delete s;
    }
    for (Model* m : models) {
        delete m;
    }

    if (basicShader) delete basicShader;
    if (treeShader) delete treeShader;
    if (clockShader) delete clockShader;
    if (ambientShader) delete ambientShader;
    if (diffuseShader) delete diffuseShader;
    if (phongShader) delete phongShader;
    if (blinnPhongShader) delete blinnPhongShader;
    if (camera) delete camera;

    if (window) glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::onWindowResize(int width, int height) {
    if (height == 0) return;
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
    basicShader = new ShaderProgram("basic.vert", "basic.frag");
    treeShader = new ShaderProgram("tree.vert", "basic.frag");
    clockShader = new ShaderProgram("clock.vert", "clock.frag");
    ambientShader = new ShaderProgram("light.vert", "ambient.frag");
    diffuseShader = new ShaderProgram("light.vert", "diffuse.frag");
    phongShader = new ShaderProgram("light.vert", "phong.frag");
    blinnPhongShader = new ShaderProgram("light.vert", "blinn.frag");

    camera = new Camera(vec3(0.0f, 0.5f, 3.0f));

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    if (height > 0) {
        camera->setAspectRatio((float)width / (float)height);
    }

    camera->attach(basicShader);
    camera->attach(treeShader);
    camera->attach(clockShader);
    camera->attach(ambientShader);
    camera->attach(diffuseShader);
    camera->attach(phongShader);
    camera->attach(blinnPhongShader);
}

void Application::createModels() {
    Model* treeModel = new Model((float*)tree, sizeof(tree) / sizeof(float), 6);
    Model* bushModel = new Model((float*)bushes, sizeof(bushes) / sizeof(float), 6);
    Model* plainModel = new Model((float*)plain, sizeof(plain) / sizeof(float), 6);

    Model* clockModelReal = new Model((float*)clockModel, sizeof(clockModel) / sizeof(float), 9);

    Model* sunModel = new Model((float*)sun, sizeof(sun) / sizeof(float), 9);
    Model* earthModel = new Model((float*)earth, sizeof(earth) / sizeof(float), 9);
    Model* moonModel = new Model((float*)moon, sizeof(moon) / sizeof(float), 9);
    Model* rocketModel = new Model((float*)rocket, sizeof(rocket) / sizeof(float), 9);

    Model* sphereModel = new Model((float*)sphere, sizeof(sphere) / sizeof(float), 6);

    vector<float> loginData = generateLoginModel();
    Model* loginModel = new Model(loginData.data(), (int)loginData.size(), 6);

    models.push_back(treeModel);
    models.push_back(bushModel);
    models.push_back(plainModel);
    models.push_back(clockModelReal);

    models.push_back(sunModel);
    models.push_back(earthModel);
    models.push_back(moonModel);
    models.push_back(rocketModel);

    models.push_back(sphereModel);

    models.push_back(loginModel);

    scenes.push_back(Scene::createForestScene(plainModel, treeModel, bushModel, clockModelReal, loginModel, basicShader, clockShader, treeShader));
    scenes.push_back(Scene::createSolarSystemScene(sunModel, earthModel, moonModel, rocketModel, loginModel, ambientShader, phongShader, blinnPhongShader, basicShader));
    scenes.push_back(Scene::createSpheresScene(sphereModel, loginModel, ambientShader, diffuseShader, phongShader, blinnPhongShader, basicShader));
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

    vec3 lightColor(1.0f, 1.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        float currentFrameTime = (float)glfwGetTime();
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        processInput(deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (currentScene == 0) {
            scenes[0]->updateClock(clockShader);
        }

        vec3 camPos = camera->getPosition();

        vec3 lightPos;
        if (currentScene == 1 || currentScene == 2) {
            lightPos = vec3(0.0f, 0.0f, 0.0f);
        }
        else {
            lightPos = vec3(0.0f, 1.0f, 5.0f);
        }

        float ambStrength = (currentScene == 2) ? 0.2f : 1.0f;

        ambientShader->use();
        ambientShader->setUniform("lightColor", lightColor);
        ambientShader->setUniform("ambientStrength", ambStrength);

        diffuseShader->use();
        diffuseShader->setUniform("lightPosition", lightPos);
        diffuseShader->setUniform("lightColor", lightColor);

        phongShader->use();
        phongShader->setUniform("lightPosition", lightPos);
        phongShader->setUniform("viewPosition", camPos);
        phongShader->setUniform("lightColor", lightColor);

        blinnPhongShader->use();
        blinnPhongShader->setUniform("lightPosition", lightPos);
        blinnPhongShader->setUniform("viewPosition", camPos);
        blinnPhongShader->setUniform("lightColor", lightColor);

        if (currentScene >= 0 && currentScene < scenes.size()) {
            scenes[currentScene]->render();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}