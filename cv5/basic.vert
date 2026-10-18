#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 attr1;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

uniform vec3 objectColor = vec3(0.1, 0.6, 0.1);
uniform float isTree = 0.0;

out vec3 finalColor;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);

    if (isTree > 0.5) {
        vec3 baseColor;
        
        if (isTree > 1.5 && gl_VertexID <= 36443) {
            baseColor = vec3(0.45, 0.25, 0.1);
        } else {
            baseColor = objectColor;
        }
        
        float shade = 0.3 + 0.7 * abs(attr1.y);
        finalColor = baseColor * shade;

    } else {
        finalColor = attr1;
    }
}