#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile) {
	GLuint vertexShader = createShaderFromFile(GL_VERTEX_SHADER, vertexFile);
	GLuint fragmentShader = createShaderFromFile(GL_FRAGMENT_SHADER, fragmentFile);

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	glLinkProgram(shaderID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(shaderID);
}

GLuint ShaderProgram::createShaderFromFile(GLenum shaderType, const char* shaderFile) {
	GLuint shaderComponentID = glCreateShader(shaderType);
	if (shaderComponentID == 0) {
		cout << "Unable to create shader" << endl;
		exit(EXIT_FAILURE);
	}

	ifstream file(shaderFile);
	if (!file.is_open()) {
		cout << "Unable to open file" << shaderFile << endl;
		glDeleteShader(shaderComponentID);
		exit(-1);
	}
	string shaderCode((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

	const char* source = shaderCode.c_str();
	glShaderSource(shaderComponentID, 1, &source, nullptr);
	glCompileShader(shaderComponentID);

	GLint success;
	glGetShaderiv(shaderComponentID, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[1024];
		glGetShaderInfoLog(shaderComponentID, sizeof(infoLog), nullptr, infoLog);
		cout << "Shader failed:\n" << infoLog << endl;
		glDeleteShader(shaderComponentID);
		exit(1);
	}
	return shaderComponentID;
}

void ShaderProgram::use() {
	glUseProgram(shaderID);
}

void ShaderProgram::setUniform(const std::string& name, float value) {
	GLint location = glGetUniformLocation(shaderID, name.c_str());

	if (location != -1)
		glUniform1f(location, value);
	else
		cout << "Warning: Uniform '" << name << "' doesn't exist!" << endl;
}
void ShaderProgram::setUniform(const std::string& name, float x, float y, float z) {
	GLint location = glGetUniformLocation(shaderID, name.c_str());

	if (location != -1) {
		glUniform3f(location, x, y, z);
	}
	else {
		cout << "Warning: Uniform '" << name << "' doesn't exist!" << endl;
	}
}