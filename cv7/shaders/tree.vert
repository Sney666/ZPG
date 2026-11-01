// ==========================================================================
// Author: Vojtěch Špalt (SPA0202)
// ==========================================================================

#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

uniform vec3 objectColor = vec3(0.1, 0.6, 0.1);
uniform float isTree = 0.0;

out vec3 finalColor;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);

    vec3 baseColor = objectColor;
    if (isTree > 0.5 && gl_VertexID <= 36443) {
        baseColor = vec3(0.45, 0.25, 0.1);
    }

    float shade = 0.3 + 0.7 * abs(normal.y);
    finalColor = baseColor * shade;
}