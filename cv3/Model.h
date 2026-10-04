#pragma once
#include <glad/gl.h>
#include "ShaderProgram.h"

class Model {
private:
	GLuint VAO, VBO;
	int vertexCount;
	ShaderProgram* shader;

	float posX, posY, posZ;
	float angle;
	float scale;

public:
	Model(float* points, int count, ShaderProgram* shaderProgram);
	~Model();

	void setPosition(float x, float y, float z);
	void setRotation(float a);
	void setScale(float s);

	void render();
};