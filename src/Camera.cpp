#include <Camera.h>

Camera::Camera() {
	projection = glm::perspective(glm::radians(fov), 1024.0f / 768.0f, 0.1f, 100.0f);

	cameraP = glm::vec3(0.0f, 0.0f, 1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraF = glm::vec3(0.0f, 0.0f, -1.0f);
}

void Camera::cameraProjection(Shader* shader) {
	view = glm::mat4(1.0f);

	view = glm::lookAt(cameraP, cameraP + cameraF, cameraUp);

	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.05f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	setCameraF(glm::normalize(direction));
}

void Camera::setCameraP(glm::vec3 cameraP) {
	this->cameraP = cameraP;
	this->cameraP.y = 2.0f;
}

glm::vec3 Camera::getCameraP() {
	return cameraP;
}

void Camera::setCameraF(glm::vec3 cameraF) {
	this->cameraF = cameraF;
}

glm::vec3 Camera::getCameraF() {
	return cameraF;
}

void Camera::setCameraUp(glm::vec3 cameraUp) {
	this->cameraUp = cameraUp;
}

glm::vec3 Camera::getCameraUp() {
	return cameraUp;
}