// ==========================================================================
// Author: Vojtěch Špalt (SPA0202)
// ==========================================================================

#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* m, ShaderProgram* s, Material* mat)
    : model(m), shader(s), transformation(nullptr), material(mat),
    color(1.0f), renderMode(0.0f), useCustomMode(false) {
}

DrawableObject::~DrawableObject() {
    if (transformation != nullptr) delete transformation;
    if (material != nullptr) delete material;
}

void DrawableObject::setTransformation(Transformation* t) {
    transformation = t;
}

void DrawableObject::setColor(vec3 c, int mode) {
    color = c;
    renderMode = (float)mode;
    useCustomMode = true;
}

void DrawableObject::render() {
    shader->use();

    mat4 M = mat4(1.0f);
    if (transformation != nullptr) {
        M = transformation->getMatrix();
    }

    shader->setUniform("modelMatrix", M);

    if (material != nullptr) {
        material->apply(shader);
    }

    if (useCustomMode) {
        if (renderMode < -0.5f) {
            shader->setUniform("useUniformColor", 0.0f);
        }
        else if (renderMode < 0.5f) {
            shader->setUniform("useUniformColor", 1.0f);
            shader->setUniform("objectColor", color.x, color.y, color.z);
        }
        else if (renderMode < 1.5f) {
            shader->setUniform("objectColor", color.x, color.y, color.z);
            shader->setUniform("isTree", 1.0f);
        }
        else {
            shader->setUniform("objectColor", color.x, color.y, color.z);
            shader->setUniform("isTree", 0.0f);
        }
    }

    glBindVertexArray(model->getVAO());
    glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());
}