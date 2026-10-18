#pragma once
#include <glad/gl.h>
#include "ShaderProgram.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Model {
private:
	GLuint VAO, VBO;
	int vertexCount;

public:
	Model(float* points, int count, int stride = 9);
	~Model();

	GLuint getVAO();
	int getVertexCount();
};