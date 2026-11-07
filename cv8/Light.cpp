// ==========================================================================
// Author: Vojtěch Špalt (SPA0202)
// ==========================================================================

#include "Light.h"

Light::Light(vec3 pos, vec3 col, float c, float l, float q) 
	: position(pos), color(col), constant(c), linear(l), quadratic(q) {}

void Light::setPosition(const vec3& pos) {
    position = pos;
}

vec3 Light::getPosition() {
    return position;
}

vec3 Light::getColor() {
    return color;
}


void Light::apply(ShaderProgram* shader) {
    if (!shader) return;
    shader->setUniform("lightPosition", position);
    shader->setUniform("lightColor", color);
    shader->setUniform("attConstant", constant);
    shader->setUniform("attLinear", linear);
    shader->setUniform("attQuadratic", quadratic);
}