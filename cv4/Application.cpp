#include "Application.h"

Application::Application() : window(nullptr), basicShader(nullptr), lightShader(nullptr), currentScene(0) {}

Application::~Application() {
    for (Scene* s : scenes) {
        delete s; 
    }
    if (basicShader) delete basicShader;
    if (lightShader) delete lightShader;
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
    lightShader = new ShaderProgram("light.vert", "light.frag");
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

    Model* sunModel = new Model((float*)sun, sizeof(sun) / sizeof(float), 9);
    Model* earthModel = new Model((float*)earth, sizeof(earth) / sizeof(float), 9);
    Model* moonModel = new Model((float*)moon, sizeof(moon) / sizeof(float), 9);

    // First scene
    Scene* scene1 = new Scene();

    TransformComposite* composite = new TransformComposite();
    composite->addTransformation(new Translate(vec3(0.5f, 0.0f, 0.0f)));
    composite->addTransformation(new Rotate(radians(45.0f), vec3(0.0f, 0.0f, 1.0f)));

    DrawableObject* triangle = new DrawableObject(triangleModel, basicShader);
    triangle->setTransformation(composite);

    scene1->addObject(triangle);
    scenes.push_back(scene1);

    // Second scene
    Scene* scene2 = new Scene();

    TransformComposite* composite2 = new TransformComposite();
    composite2->addTransformation(new Rotate(radians(45.0f), vec3(0.0f, 0.0f, 1.0f)));
    composite2->addTransformation(new Translate(vec3(0.5f, 0.0f, 0.0f)));

    DrawableObject* triangle2 = new DrawableObject(triangleModel, basicShader);
    triangle2->setTransformation(composite2);

    scene2->addObject(triangle2);
    scenes.push_back(scene2);

    // Third scene
    Scene* scene3 = new Scene();

    for (int i = 0; i < 25; i++) {
        float treeX = (rand() % 200 - 100) / 100.0f;
        float treeY = (rand() % 200 - 100) / 100.0f;

        TransformComposite* treeComp = new TransformComposite();
        treeComp->addTransformation(new Translate(glm::vec3(treeX, treeY, 0.0f)));
        treeComp->addTransformation(new Scale(glm::vec3(0.08f)));

        DrawableObject* treeObj = new DrawableObject(treeModel, basicShader);
        treeObj->setTransformation(treeComp);
        scene3->addObject(treeObj);
    }

    for (int i = 0; i < 50; i++) {
        float bushX = (rand() % 200 - 100) / 100.0f;
        float bushY = (rand() % 200 - 100) / 100.0f;

        TransformComposite* bushComp = new TransformComposite();
        bushComp->addTransformation(new Translate(glm::vec3(bushX, bushY, 0.0f)));
        bushComp->addTransformation(new Scale(glm::vec3(0.4f)));

        DrawableObject* bushObj = new DrawableObject(bushModel, basicShader);
        bushObj->setTransformation(bushComp);
        scene3->addObject(bushObj);
    }

    scenes.push_back(scene3);

    // Fourth scene
    Scene* scene4 = new Scene();

    TransformComposite* sunComp = new TransformComposite();
    sunComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 0.0f), 0.5f));
    sunComp->addTransformation(new Scale(vec3(0.4f)));

    DrawableObject* sunObj = new DrawableObject(sunModel, lightShader);
    sunObj->setTransformation(sunComp);
    scene4->addObject(sunObj);

    TransformComposite* earthComp = new TransformComposite();
    earthComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 0.0f), 1.0f));
    earthComp->addTransformation(new Translate(vec3(0.7f, 0.0f, 0.0f)));
    earthComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 0.0f), 3.0f));
    earthComp->addTransformation(new Scale(vec3(0.15f)));

    DrawableObject* earthObj = new DrawableObject(earthModel, lightShader);
    earthObj->setTransformation(earthComp);
    scene4->addObject(earthObj);

    TransformComposite* moonComp = new TransformComposite();
    moonComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 0.0f), 1.0f));
    moonComp->addTransformation(new Translate(vec3(0.7f, 0.0f, 0.0f)));
    moonComp->addTransformation(new DynamicRotate(vec3(0.0f, 1.0f, 0.0f), 4.0f));
    moonComp->addTransformation(new Translate(vec3(0.3f, 0.0f, 0.0f)));
    moonComp->addTransformation(new Scale(vec3(0.05f)));

    DrawableObject* moonObj = new DrawableObject(moonModel, lightShader);
    moonObj->setTransformation(moonComp);
    scene4->addObject(moonObj);

    scenes.push_back(scene4);
}

void Application::run() {
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