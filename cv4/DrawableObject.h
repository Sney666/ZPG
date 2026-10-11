#pragma once
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

class DrawableObject
{
private:
	Model* model;
	ShaderProgram* shader;
	Transformation* transformation;
public:
	DrawableObject(Model* m, ShaderProgram* s);
	void setTransformation(Transformation* t);
	void render();
};

