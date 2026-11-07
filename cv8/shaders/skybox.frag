// ==========================================================================
// Author: Vojtěch Špalt (SPA0202)
// ==========================================================================

#version 330 core
in vec3 fragTexCoords;
out vec4 FragColor;

uniform samplerCube textureUnitID;

void main() {
    FragColor = texture(textureUnitID, fragTexCoords);
}