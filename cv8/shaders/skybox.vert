// ==========================================================================
// Author: Vojtěch Špalt (SPA0202)
// ==========================================================================

#version 330 core
layout(location = 0) in vec3 position;

uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

out vec3 fragTexCoords;

void main() {
    fragTexCoords = position;
    mat4 viewNoTranslation = mat4(mat3(viewMatrix));
    gl_Position = projectionMatrix * viewNoTranslation * vec4(position, 1.0);
}