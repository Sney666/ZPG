#pragma once
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include <glm/glm.hpp>

using namespace glm;

class DrawableObject
{
private:
	Model* model;
	ShaderProgram* shader;
	Transformation* transformation;

	vec3 color;
	float renderMode;
	bool useCustomMode;

public:
	DrawableObject(Model* m, ShaderProgram* s);
	~DrawableObject();

	void setTransformation(Transformation* t);
	void setColor(vec3 c, int isTree = 0);
	void render();
};

