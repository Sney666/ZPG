#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

uniform mat4 modelMatrix;

out vec3 vertexColor;
out vec3 FragPos;
out vec3 Normal;

void main() {
    gl_Position = modelMatrix * vec4(position, 1.0);
    vertexColor = color;
    FragPos = vec3(modelMatrix * vec4(position, 1.0));
    Normal = mat3(transpose(inverse(modelMatrix))) * normal; 
}