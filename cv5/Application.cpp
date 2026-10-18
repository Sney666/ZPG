#include "Application.h"

Application::Application() : window(nullptr), basicShader(nullptr), clockShader(nullptr), camera(nullptr), currentScene(0) {}

Application::~Application() {
    for (Scene* s : scenes) {
        delete s; 
    }
    for (Model* m : models) {
        delete m;
    }

    if (basicShader) delete basicShader;
    if (clockShader) delete clockShader;
    if (camera) delete camera;

    if (window) glfwDestroyWindow(window);
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
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);

    srand(time(NULL));
}

void Application::createShaders() {
    basicShader = new ShaderProgram("basic.vert", "basic.frag");
    clockShader = new ShaderProgram("clock.vert", "clock.frag");

    camera = new Camera(vec3(0.0f, 0.5f, 3.0f));

    camera->attach(basicShader);
    camera->attach(clockShader);
}

void Application::createModels() {
    float trianglePoints[] = {
         0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f
    };

    Model* triangleModel = new Model(trianglePoints, sizeof(trianglePoints) / sizeof(float), 6);

    Model* treeModel = new Model((float*)tree, sizeof(tree) / sizeof(float), 6);
    Model* bushModel = new Model((float*)bushes, sizeof(bushes) / sizeof(float), 6);
    Model* plainModel = new Model((float*)plain, sizeof(plain) / sizeof(float), 6);

    Model* clockModelReal = new Model((float*)clockModel, sizeof(clockModel) / sizeof(float), 9);

    Model* sunModel = new Model((float*)sun, sizeof(sun) / sizeof(float), 9);
    Model* earthModel = new Model((float*)earth, sizeof(earth) / sizeof(float), 9);
    Model* moonModel = new Model((float*)moon, sizeof(moon) / sizeof(float), 9);

    std::vector<float> loginData = generateLoginModel();
    Model* loginModel = new Model(loginData.data(), loginData.size(), 6);

    models.push_back(triangleModel);
    models.push_back(treeModel);
    models.push_back(bushModel);
    models.push_back(plainModel);
    models.push_back(clockModelReal);
    models.push_back(sunModel);
    models.push_back(earthModel);
    models.push_back(moonModel);
    models.push_back(loginModel);

    // First scene
    Scene* scene1 = new Scene();

    // Triangle
    TransformComposite* composite = new TransformComposite();
    composite->addTransformation(new Translate(vec3(0.5f, 0.0f, 0.0f)));
    composite->addTransformation(new Rotate(radians(45.0f), vec3(0.0f, 0.0f, 1.0f)));
    DrawableObject* triangle = new DrawableObject(triangleModel, basicShader);
    triangle->setTransformation(composite);
    triangle->setColor(vec3(1.0f), -1);
    scene1->addObject(triangle);

    // Login
    TransformComposite* loginComp1 = new TransformComposite();
    loginComp1->addTransformation(new Translate(vec3(0.0f, 1.5f, -2.0f)));
    loginComp1->addTransformation(new Scale(vec3(0.5f)));
    DrawableObject* loginObj1 = new DrawableObject(loginModel, basicShader);
    loginObj1->setTransformation(loginComp1);
    loginObj1->setColor(vec3(1.0f), -1);
    scene1->addObject(loginObj1);

    scenes.push_back(scene1);

    // Second scene
    Scene* scene2 = new Scene();

    // Triangle
    TransformComposite* composite2 = new TransformComposite();
    composite2->addTransformation(new Rotate(radians(45.0f), vec3(0.0f, 0.0f, 1.0f)));
    composite2->addTransformation(new Translate(vec3(0.5f, 0.0f, 0.0f)));
    DrawableObject* triangle2 = new DrawableObject(triangleModel, basicShader);
    triangle2->setTransformation(composite2);
    triangle2->setColor(vec3(1.0f), -1);
    scene2->addObject(triangle2);

    // Login
    TransformComposite* loginComp2 = new TransformComposite();
    loginComp2->addTransformation(new Translate(vec3(0.0f, 1.5f, -2.0f)));
    loginComp2->addTransformation(new Scale(vec3(0.5f)));
    DrawableObject* loginObj2 = new DrawableObject(loginModel, basicShader);
    loginObj2->setTransformation(loginComp2);
    loginObj2->setColor(vec3(1.0f), -1);
    scene2->addObject(loginObj2);

    scenes.push_back(scene2);

    // Third scene
    Scene* scene3 = new Scene();

    // Plain
    TransformComposite* plainComp = new TransformComposite();
    plainComp->addTransformation(new Scale(vec3(15.0f, 1.0f, 15.0f)));

    DrawableObject* plainObj = new DrawableObject(plainModel, basicShader);
    plainObj->setTransformation(plainComp);
    plainObj->setColor(vec3(0.2f, 0.35f, 0.1f), 0);
    scene3->addObject(plainObj);

    // Trees
    for (int i = 0; i < 100; i++) {
        float treeX = (rand() % 1400 - 700) / 100.0f;
        float treeZ = (rand() % 1400 - 700) / 100.0f;
        float treeRot = radians((float)(rand() % 360));
        float treeScale = 0.12f + (rand() % 100) / 1000.0f;

        TransformComposite* treeComp = new TransformComposite();
        treeComp->addTransformation(new Translate(vec3(treeX, 0.0f, treeZ)));
        treeComp->addTransformation(new Rotate(treeRot, vec3(0.0f, 1.0f, 0.0f)));
        treeComp->addTransformation(new Scale(vec3(treeScale)));

        float greenShade = 0.35f + (rand() % 55) / 100.0f;
        float redTint = (rand() % 20) / 100.0f;

        DrawableObject* treeObj = new DrawableObject(treeModel, basicShader);
        treeObj->setTransformation(treeComp);
        treeObj->setColor(vec3(redTint, greenShade, 0.05f), 1);
        scene3->addObject(treeObj);
    }

    // Bushes
    for (int i = 0; i < 200; i++) {
        float bushX = (rand() % 1400 - 700) / 100.0f;
        float bushZ = (rand() % 1400 - 700) / 100.0f;
        float bushRot = radians((float)(rand() % 360));
        float bushScale = 0.5f + (rand() % 40) / 100.0f;

        TransformComposite* bushComp = new TransformComposite();
        bushComp->addTransformation(new Translate(vec3(bushX, 0.0f, bushZ)));
        bushComp->addTransformation(new Rotate(bushRot, vec3(0.0f, 1.0f, 0.0f)));
        bushComp->addTransformation(new Scale(vec3(bushScale)));

        float bushGreen = 0.3f + (rand() % 40) / 100.0f;

        DrawableObject* bushObj = new DrawableObject(bushModel, basicShader);
        bushObj->setTransformation(bushComp);
        bushObj->setColor(vec3(0.1f, bushGreen, 0.1f), 0);
        scene3->addObject(bushObj);
    }

    // Clocks
    TransformComposite* clock1Comp = new TransformComposite();
    clock1Comp->addTransformation(new Translate(vec3(-1.0f, 0.8f, 1.0f)));
    clock1Comp->addTransformation(new Scale(vec3(-0.3f, 0.3f, 0.3f)));

    DrawableObject* clock1 = new DrawableObject(clockModelReal, clockShader);
    clock1->setTransformation(clock1Comp);
    scene3->addObject(clock1);

    TransformComposite* clock2Comp = new TransformComposite();
    clock2Comp->addTransformation(new Translate(vec3(2.5f, 1.2f, -2.0f)));
    clock2Comp->addTransformation(new Scale(vec3(-0.3, 0.3f, 0.3f)));

    DrawableObject* clock2 = new DrawableObject(clockModelReal, clockShader);
    clock2->setTransformation(clock2Comp);
    scene3->addObject(clock2);

    // Login
    TransformComposite* loginComp = new TransformComposite();
    loginComp->addTransformation(new Translate(vec3(0.0f, 2.5f, -3.0f)));

    DrawableObject* loginObj = new DrawableObject(loginModel, basicShader);
    loginObj->setTransformation(loginComp);
    loginObj->setColor(vec3(1.0f), -1);
    scene3->addObject(loginObj);

    scenes.push_back(scene3);

    // Fourth scene
    Scene* scene4 = new Scene();

    // Sun
    TransformComposite* sunComp = new TransformComposite();
    sunComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 0.0f), 0.5f));
    sunComp->addTransformation(new Scale(vec3(0.4f)));

    DrawableObject* sunObj = new DrawableObject(sunModel, basicShader);
    sunObj->setTransformation(sunComp);
    sunObj->setColor(vec3(1.0f), -1);
    scene4->addObject(sunObj);

    // Earth
    TransformComposite* earthComp = new TransformComposite();
    earthComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 0.0f), 1.0f));
    earthComp->addTransformation(new Translate(vec3(0.7f, 0.0f, 0.0f)));
    earthComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 0.0f), 3.0f));
    earthComp->addTransformation(new Scale(vec3(0.15f)));

    DrawableObject* earthObj = new DrawableObject(earthModel, basicShader);
    earthObj->setTransformation(earthComp);
    sunObj->setColor(vec3(1.0f), -1);
    scene4->addObject(earthObj);

    // Moon
    TransformComposite* moonComp = new TransformComposite();
    moonComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 0.0f), 1.0f));
    moonComp->addTransformation(new Translate(vec3(0.7f, 0.0f, 0.0f)));
    moonComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 0.0f), 4.0f));
    moonComp->addTransformation(new Translate(vec3(0.3f, 0.0f, 0.0f)));
    moonComp->addTransformation(new Scale(vec3(0.05f)));

    DrawableObject* moonObj = new DrawableObject(moonModel, basicShader);
    moonObj->setTransformation(moonComp);
    sunObj->setColor(vec3(1.0f), -1);
    scene4->addObject(moonObj);

    // Login 
    TransformComposite* loginComp4 = new TransformComposite();
    loginComp4->addTransformation(new Translate(vec3(0.0f, 1.5f, -2.0f)));
    loginComp4->addTransformation(new Scale(vec3(0.5f)));
    DrawableObject* loginObj4 = new DrawableObject(loginModel, basicShader);
    loginObj4->setTransformation(loginComp4);
    loginObj4->setColor(vec3(1.0f), -1);
    scene4->addObject(loginObj4);

    scenes.push_back(scene4);
}

void Application::processInput(float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) currentScene = 0;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) currentScene = 1;
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) currentScene = 2;
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) currentScene = 3;

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

void Application::updateClock() {
    time_t now = time(0);
    tm localTime;
    localtime_s(&localTime, &now);

    float seconds = (float)localTime.tm_sec;
    float minutes = (float)localTime.tm_min + seconds / 60.0f;
    float hours = (float)(localTime.tm_hour % 12) + minutes / 60.0f;

    float twoPi = -6.2831853f;
    float secAngle = (seconds / 60.0f) * twoPi;
    float minAngle = (minutes / 60.0f) * twoPi;
    float hourAngle = (hours / 12.0f) * twoPi;

    clockShader->use();
    clockShader->setUniform("secAngle", secAngle);
    clockShader->setUniform("minAngle", minAngle);
    clockShader->setUniform("hourAngle", hourAngle);
}

void Application::run() {
    float lastFrameTime = (float)glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        float currentFrameTime = (float)glfwGetTime();
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        processInput(deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (currentScene == 2) {
            updateClock();
        }

        if (currentScene >= 0 && currentScene < scenes.size()) {
            scenes[currentScene]->render();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}