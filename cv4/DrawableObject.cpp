#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* m, ShaderProgram* s) : model(m), shader(s), transformation(nullptr) {}

void DrawableObject::setTransformation(Transformation* t) {
	transformation = t;
}

void DrawableObject::render() {
	shader->use();

	glm::mat4 M = glm::mat4(1.0f);
	if (transformation != nullptr) {
		M = transformation->getMatrix();
	}

	shader->setUniform("modelMatrix", M);

	glBindVertexArray(model->getVAO());
	glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());
}