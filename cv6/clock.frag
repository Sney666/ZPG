// ==========================================================================
// Author: Vojtěch Špalt (SPA0202)
// ==========================================================================

#version 330 core
in vec3 vertexColor;
in vec3 fragNormal;

out vec4 FragColor;

void main() {
    vec3 norm = normalize(fragNormal);
    float shade = 0.6 + 0.4 * abs(norm.z);
    FragColor = vec4(vertexColor * shade, 1.0);
}