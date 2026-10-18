#include "Camera.h"

Camera::Camera(vec3 startPositon) {
	eye = startPositon;
	up = vec3(0.0f, 1.0f, 0.0f);
	alpha = 1.57f;
	fi = -1.57f;

	updateCameraVectors();
}

void Camera::updateCameraVectors() {
	target.x = sin(alpha) * cos(fi);
	target.z = sin(alpha) * sin(fi);
	target.y = cos(alpha);

	target = normalize(target);
}

void Camera::attach(Observer* observer) {
	observers.push_back(observer);
	observer->notify(getViewMatrix(), getProjectionMatrix(4.0f / 3.0f));
}

void Camera::detach(Observer* observer) {
	observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
}

void Camera::notifyObservers() {
	mat4 view = getViewMatrix();
	mat4 projection = getProjectionMatrix(4.0 / 3.0f);

	for (Observer* o : observers) {
		o->notify(view, projection);
	}
}

mat4 Camera::getViewMatrix() {
	return lookAt(eye, eye + target, up);
}

mat4 Camera::getProjectionMatrix(float windowRatio) {
	return perspective(radians(60.0f), windowRatio, 0.1f, 100.0f);
}

void Camera::moveForward(float speed) {
	eye += target * speed;
	notifyObservers();
}

void Camera::moveBackward(float speed) {
	eye -= target * speed;
	notifyObservers();
}

void Camera::moveLeft(float speed) {
	vec3 rightVector = normalize(cross(target, up));
	eye -= rightVector * speed;
	notifyObservers();
}

void Camera::moveRight(float speed) {
	vec3 rightVector = normalize(cross(target, up));
	eye += rightVector * speed;
	notifyObservers();
}

void Camera::updateAngles(float deltaAlpha, float deltaFi) {
	alpha += deltaAlpha;
	fi += deltaFi;

	if (alpha <= 0.01f) alpha = 0.01f;
	if (alpha >= 3.13f) alpha = 3.13f;

	updateCameraVectors();
	notifyObservers();
}