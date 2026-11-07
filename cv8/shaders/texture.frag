// ==========================================================================
// Author: Vojtěch Špalt (SPA0202)
// ==========================================================================

#version 330 core

in vec2 uv;
in vec3 normal;
in vec3 position;

uniform sampler2D textureUnitID;

out vec4 FragColor;

void main()
{
    FragColor = vec4(texture(textureUnitID, uv));
}