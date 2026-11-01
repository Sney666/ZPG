// ==========================================================================
// Author: Vojtěch Špalt (SPA0202)
// ==========================================================================

#include "Material.h"

Material::Material(float amb, float diff, float spec, float shin) : ambient(amb), diffuse(diff), specular(spec), shininess(shin) {}

void Material::apply(ShaderProgram* shader) {
    if (!shader) return;
    shader->setUniform("ambientStrength", ambient);
    shader->setUniform("diffuseStrength", diffuse);
    shader->setUniform("specularStrength", specular);
    shader->setUniform("shininess", shininess);
}