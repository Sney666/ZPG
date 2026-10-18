#pragma once
#include <glad/gl.h>
#include <string>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Observer.h"

using namespace std;

class ShaderProgram : public Observer {
private:
	GLuint shaderID;

	GLuint createShaderFromFile(GLenum shaderType, const char* shaderFile);
public:
	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	~ShaderProgram();
	
	void use();
	void setUniform(const string& name, float value);
	void setUniform(const string& name, float x, float y, float z);
	void setUniform(const string& name, const mat4& matrix);
	void notify(const mat4& viewMatrix, const mat4& projectionMatrix) override;
};