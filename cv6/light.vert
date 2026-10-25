// ==========================================================================
// Author: Vojtěch Špalt (SPA0202)
// ==========================================================================

#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

uniform vec3 objectColor = vec3(1.0, 1.0, 1.0);
uniform float useUniformColor = 0.0;

out vec3 FragPos;
out vec3 Normal;
out vec3 BaseColor;

void main() {
    FragPos = vec3(modelMatrix * vec4(position, 1.0));
    Normal = mat3(transpose(inverse(modelMatrix))) * normal;

    if (useUniformColor > 0.5) {
        BaseColor = objectColor;
    } else {
        BaseColor = color;
    }

    gl_Position = projectionMatrix * viewMatrix * vec4(FragPos, 1.0);
}