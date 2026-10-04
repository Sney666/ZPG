#include "Model.h"

Model::Model(float* points, int count, ShaderProgram* shaderProgram) : VAO(0), VBO(0), vertexCount(count), shader(shaderProgram), posX(0), posY(0), posZ(0), scale(1), angle(0) {
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, count * 6 * sizeof(float), points, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
}

Model::~Model() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Model::setPosition(float x, float y, float z) {
	posX = x;
	posY = y;
	posZ = z;
}

void Model::setRotation(float a) {
	angle = a;
}

void Model::setScale(float s) {
	scale = s;
}

void Model::render() {
    shader->use();
    shader->setUniform("offset", posX, posY, posZ);
    shader->setUniform("scale", scale);
    shader->setUniform("angle", angle);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}