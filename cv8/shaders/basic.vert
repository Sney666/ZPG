// ==========================================================================
// Author: Vojtěch Špalt (SPA0202)
// ==========================================================================

#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 attr1;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

uniform vec3 objectColor = vec3(1.0, 1.0, 1.0);
uniform float useUniformColor = 0.0;

out vec3 finalColor;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);

    if (useUniformColor > 0.5) {
        float shade = 0.3 + 0.7 * abs(attr1.y);
        finalColor = objectColor * shade;
    } else {
        finalColor = attr1;
    }
}