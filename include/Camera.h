#pragma once

#include <Shader.h>

class Camera {
public:
	glm::vec3 cameraP = glm::vec3(0.0f, 0.0f, 8.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraF = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	bool firstMouse = true;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX = 400;
	float lastY = 300;
	float fov = 45.0f;
	bool check = false;

	//// Constructor with vectors
	//Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM);
	//// Constructor with scalar values
	//Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM);

	void transform(Shader* shader);

	float startRun();

	float endRun();

	void input(GLFWwindow* window);

	void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	//void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);

	//private:
	//	void updateCameraVectors();
};