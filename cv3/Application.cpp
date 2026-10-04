#include "Application.h"

Application::Application() : window(nullptr), myShader(nullptr), currentScene(0) {}

Application::~Application() {
    for (Scene* s : scenes) {
        delete s; 
    }
    if (myShader) delete myShader;
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
}

void Application::createShaders() {
    myShader = new ShaderProgram("basic.vert", "basic.frag");
}

void Application::createModels() {
    vector<float> loginData = generateLoginModel();
    int loginVertexCount = loginData.size() / 6;

    // 1
    Scene* scene = new Scene();
    float trianglePoints[] = {
         0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f
    };
    Model* triangle = new Model(trianglePoints, 3, myShader);
    scene->addModel(triangle);

    Model* signature = new Model(loginData.data(), loginVertexCount, myShader);
    signature->setScale(0.2f);
    signature->setPosition(-0.5f, 0.8f, 0.0f);
    scene->addModel(signature);

    scenes.push_back(scene);

    // 2
    Scene* scene2 = new Scene();
    int sphereVertexCount = (int)(sizeof(sphere) / (6 * sizeof(float)));
    Model* mySphere = new Model((float*)sphere, sphereVertexCount, myShader);
    mySphere->setScale(0.5f);
    scene2->addModel(mySphere);

    Model* signature2 = new Model(loginData.data(), loginVertexCount, myShader);
    signature2->setScale(0.2f);
    signature2->setPosition(-0.5f, 0.8f, 0.0f);
    scene2->addModel(signature2);

    scenes.push_back(scene2);

    // 3

    Scene* scene3 = new Scene();

    Model* sun = new Model((float*)sphere, sphereVertexCount, myShader);
    sun->setPosition(0.7f, 0.7f, 0.0f);
    sun->setScale(0.25f);
    scene3->addModel(sun);

    int treeVertexCount = sizeof(tree) / (6 * sizeof(float));
    int bushVertexCount = sizeof(bushes) / (6 * sizeof(float));

    for (int i = 0; i < 15; i++) {
        Model* myTree = new Model((float*)tree, treeVertexCount, myShader);
        float treeX = -0.85f + (i * 0.12f);
        float treeY = -0.6f + ((i % 3) * 0.25f);
        myTree->setPosition(treeX, treeY, 0.0f);

        myTree->setScale(0.08f);
        scene3->addModel(myTree);
    }

    for (int i = 0; i < 30; i++) {
        Model* myBush = new Model((float*)bushes, bushVertexCount, myShader);
        float bushX = -1.0f + (i * 0.07f);
        float bushY = -0.7f - ((i % 2) * 0.1f);
        myBush->setPosition(bushX, bushY, 0.0f);

        myBush->setScale(0.4f);
        scene3->addModel(myBush);
    }

    Model* signature3 = new Model(loginData.data(), loginVertexCount, myShader);
    signature3->setScale(0.2f);
    signature3->setPosition(-0.5f, 0.8f, 0.0f);
    scene3->addModel(signature3);

    scenes.push_back(scene3);

    // 4
    Scene* scene4 = new Scene();
    Model* bigLogin = new Model(loginData.data(), loginVertexCount, myShader);
    bigLogin->setScale(0.4f);
    scene4->addModel(bigLogin);
    scenes.push_back(scene4);
}

void Application::run() {
    /*
    // PREVIOUS STEP: TRANSFORMATIONS VIA KEYBOARD

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) posX += 0.01f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) posX -= 0.01f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) posY += 0.01f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) posY -= 0.01f;

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) angle += 0.02f;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) angle -= 0.02f;

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) scale += 0.01f;
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) scale -= 0.01f;

    // scenes[currentScene]->models[0]->setPosition(posX, posY, 0.0f);
    // scenes[currentScene]->models[0]->setScale(scale);
    // scenes[currentScene]->models[0]->setRotation(angle);
    */

    while (!glfwWindowShouldClose(window)) {

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) currentScene = 0;
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) currentScene = 1;
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) currentScene = 2;
        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) currentScene = 3;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (currentScene >= 0 && currentScene < scenes.size()) {
            scenes[currentScene]->render();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}