#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <vector>
#include <GLFW/glfw3.h>

using namespace glm;

class Transformation {
public:
    virtual mat4 getMatrix() = 0;
    virtual ~Transformation() = default;
};

class Translate : public Transformation {
private:
    vec3 position;
public:
    Translate(vec3 pos);
    mat4 getMatrix() override;
};

class Rotate : public Transformation {
private:
    float angle;
    vec3 axis;
public:
    Rotate(float ang, vec3 ax);
    mat4 getMatrix() override;
};

class DynamicRotate : public Transformation {
private:
    vec3 axis;
    float speed;
public:
    DynamicRotate(vec3 ax, float sp);
    mat4 getMatrix() override;
};

class Scale : public Transformation {
private:
    vec3 scaleVec;
public:
    Scale(vec3 s);
    mat4 getMatrix() override;
};

class TransformComposite : public Transformation {
private:
    std::vector<Transformation*> transformations;
public:
    void addTransformation(Transformation* t);
    mat4 getMatrix() override;
    ~TransformComposite();
};