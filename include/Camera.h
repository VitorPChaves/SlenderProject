#pragma once

#include <Shader.h>

class Camera {
public:
	glm::vec3 cameraP = glm::vec3(0.0f, 0.0f, 10.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraF = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraS = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 view;
	glm::mat4 projection;

	bool firstMouse = true;
	bool running = false;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX = 400;
	float lastY = 300;
	float fov = 45.0f;
	float speed = 3.0f;

	float runningStartTime;
	float runningEndTime = glfwGetTime();

	Camera();
	void cameraProjection(Shader* shader);
	void input(GLFWwindow* window);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};