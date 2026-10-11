#pragma once
#include <glad/gl.h>
#include <string>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class ShaderProgram {
private:
	GLuint shaderID;

	GLuint createShaderFromFile(GLenum shaderType, const char* shaderFile);
public:
	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	~ShaderProgram();
	
	void use();
	void setUniform(const string& name, float value);
	void setUniform(const string& name, float x, float y, float z);
	void setUniform(const std::string& name, const glm::mat4& matrix);
};