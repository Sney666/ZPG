// ==========================================================================
// Author: Vojtěch Špalt (SPA0202)
// ==========================================================================

#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec3 BaseColor;

out vec4 FragColor;

uniform vec3 lightColor;
uniform float ambientStrength = 1.0;

void main() {
    vec3 ambient = ambientStrength * lightColor;
    vec3 result = ambient * BaseColor;
    FragColor = vec4(result, 1.0);
}