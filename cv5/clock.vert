#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

uniform float secAngle = 0.0;
uniform float minAngle = 0.0;
uniform float hourAngle = 0.0;

out vec3 vertexColor;
out vec3 fragNormal;

vec3 rotateZ(vec3 pos, float angle) {
    float c = cos(angle);
    float s = sin(angle);
    return vec3(
        pos.x * c - pos.y * s,
        pos.x * s + pos.y * c,
        pos.z
    );
}

void main() {
    vec3 localPos = position;

    if (color.r > 0.9 && color.g < 0.1 && color.b < 0.1) {
        localPos = rotateZ(localPos, secAngle);
    }
    else if (color.g > 0.9 && color.r < 0.1 && color.b < 0.1) {
        localPos = rotateZ(localPos, minAngle);
    }
    else if (color.b > 0.9 && color.r < 0.1 && color.g < 0.1) {
        localPos = rotateZ(localPos, hourAngle);
    }

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(localPos, 1.0);
    if (color.r > 0.8 && color.g > 0.8 && color.b < 0.2) {
        vertexColor = vec3(5.0 / 255.0, 195.0 / 255.0, 222.0 / 255.0);
    } else {
        vertexColor = color;
    }
    fragNormal = mat3(transpose(inverse(modelMatrix))) * normal;
}