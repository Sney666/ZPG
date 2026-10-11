#include "Transformation.h"

Translate::Translate(vec3 pos) : position(pos) {}

mat4 Translate::getMatrix() {
    return translate(mat4(1.0f), position);
}

Rotate::Rotate(float ang, vec3 ax) : angle(ang), axis(ax) {}

mat4 Rotate::getMatrix() {
    return rotate(mat4(1.0f), angle, axis);
}

DynamicRotate::DynamicRotate(vec3 ax, float sp) : axis(ax), speed(sp) {}

mat4 DynamicRotate::getMatrix() {
    float time = (float)glfwGetTime();
    time *= speed;
    return rotate(mat4(1.0f), time, axis);
}

Scale::Scale(vec3 s) : scaleVec(s) {}

mat4 Scale::getMatrix() {
    return scale(mat4(1.0f), scaleVec);
}

void TransformComposite::addTransformation(Transformation* t) {
    transformations.push_back(t);
}

mat4 TransformComposite::getMatrix() {
    mat4 M = mat4(1.0f);
    for (Transformation* t : transformations) {
        M *= t->getMatrix();
    }
    return M;
}

TransformComposite::~TransformComposite() {
    for (Transformation* t : transformations) {
        delete t;
    }
}