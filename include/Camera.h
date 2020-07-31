#pragma once
#include <Shader.h>

class Camera {
public:

	Camera();
	void cameraProjection(Shader* shader);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void setCameraP(glm::vec3 cameraP);
	glm::vec3 getCameraP();
	glm::vec3 getCameraF();
	glm::vec3 getCameraUp();

private:
	glm::vec3 cameraP;
	glm::vec3 cameraUp;
	glm::vec3 cameraF;

	glm::mat4 view;
	glm::mat4 projection;

	bool firstMouse = true;

	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX = 400;
	float lastY = 300;
	float fov = 45.0f;
	float speed = 3.0f;

	void setCameraF(glm::vec3 cameraF);
	void setCameraUp(glm::vec3 cameraUp);
};