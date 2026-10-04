#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform vec3 offset;
uniform float scale;
uniform float angle;

void main() {
	float scaledX = aPos.x * scale;
    	float scaledY = aPos.y * scale;
    	float scaledZ = aPos.z * scale;

	float rotatedX = cos(angle) * scaledX + sin(angle) * scaledZ;
	float rotatedY = scaledY;
	float rotatedZ = -sin(angle) * scaledX + cos(angle) * scaledZ;

    	gl_Position = vec4(rotatedX + offset.x, rotatedY + offset.y, rotatedZ + offset.z, 1.0);

    	ourColor = aColor;
}