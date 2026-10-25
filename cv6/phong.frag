// ==========================================================================
// Author: Vojtěch Špalt (SPA0202)
// ==========================================================================

#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec3 BaseColor;

out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

void main() {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 specular = vec3(0.0);
    if (diff > 0.0) {
        float specularStrength = 0.5;
        vec3 viewDir = normalize(viewPosition - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
        specular = specularStrength * spec * lightColor;
    }

    vec3 result = (ambient + diffuse) * BaseColor + specular;
    FragColor = vec4(result, 1.0);
}