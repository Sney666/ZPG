#pragma once
#include <glm/glm.hpp>

using namespace glm;

class Observer {
public:
	virtual void notify(const mat4& viewMatrix, const mat4& projectionMatrix) = 0;
};