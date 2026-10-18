#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* m, ShaderProgram* s) : model(m), shader(s), transformation(nullptr), color(1.0f), renderMode(0.0f), useCustomMode(false) {}

DrawableObject::~DrawableObject() {
	if (transformation != nullptr) {
		delete transformation;
	}
}

void DrawableObject::setTransformation(Transformation* t) {
	transformation = t;
}

void DrawableObject::setColor(vec3 c, int isTree) {
	color = c;
	if (isTree == 1) renderMode = 2.0f;
	else if (isTree == 0) renderMode = 1.0f;
	else renderMode = 0.0f;
	useCustomMode = true;
}

void DrawableObject::render() {
	shader->use();

	mat4 M = mat4(1.0f);
	if (transformation != nullptr) {
		M = transformation->getMatrix();
	}

	shader->setUniform("modelMatrix", M);

	if (useCustomMode) {
		shader->setUniform("objectColor", color.x, color.y, color.z);
		shader->setUniform("isTree", renderMode);
	}

	glBindVertexArray(model->getVAO());
	glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());
}