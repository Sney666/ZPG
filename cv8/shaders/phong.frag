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

uniform float ambientStrength = 0.1;
uniform float diffuseStrength = 1.0;
uniform float specularStrength = 0.5;
uniform float shininess = 32.0;

uniform float attConstant = 1.0;
uniform float attLinear = 0.09;
uniform float attQuadratic = 0.032;

void main() {
    float dist = length(lightPosition - FragPos);
    float att = 1.0 / (attConstant + attLinear * dist + attQuadratic * (dist * dist));
    att = clamp(att, 0.0, 1.0);

    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * diff * lightColor;

    vec3 viewDir = normalize(viewPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    
    // Test
    /*float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0);
    vec3 specular = specularStrength * spec * lightColor;*/

    vec3 specular = vec3(0.0);
    if (diff > 0.0) {
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        specular = specularStrength * spec * lightColor;
    }

    ambient  *= att;
    diffuse  *= att;
    specular *= att;

    vec3 result = (ambient + diffuse) * BaseColor + specular;
    FragColor = vec4(result, 1.0);
}