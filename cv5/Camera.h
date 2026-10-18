#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Observer.h"
#include <algorithm>

using namespace glm;
using namespace std;

class Camera
{
private:
	vec3 eye;
	vec3 target;
	vec3 up;

	float alpha;
	float fi;

	vector<Observer*> observers;

	void updateCameraVectors();

public:
	Camera(vec3 startPosition);
	
	void attach(Observer* observer);
	void detach(Observer* observer);
	void notifyObservers();

	mat4 getViewMatrix();
	mat4 getProjectionMatrix(float windowRatio);

	void moveForward(float speed);
	void moveBackward(float speed);
	void moveLeft(float speed);
	void moveRight(float speed);
	void updateAngles(float deltaAlpha, float deltaFi);
};

