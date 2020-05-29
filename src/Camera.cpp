#include <Camera.h>
#include <Windows.h>

Camera::Camera() 
{ }

void Camera::cameraProjection(Shader* shader) {
	view = glm::mat4(1.0f);

	view = glm::lookAt(cameraP, cameraP + cameraF, cameraUp);

	shader->use();

	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
}

void Camera::input(GLFWwindow* window) {
	const auto cameraFonXZ = glm::normalize(glm::vec3(cameraF.x, 0.0f, cameraF.z));
	float currentFrame = glfwGetTime();
	float cameraSpeed = speed * deltaTime;

	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	cameraP.y = 2.0f;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraP += cameraSpeed * cameraFonXZ;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraP -= cameraSpeed * cameraFonXZ;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraP += glm::normalize(glm::cross(cameraFonXZ, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraP -= glm::normalize(glm::cross(cameraFonXZ, cameraUp)) * cameraSpeed;

	// sets running to false and returns to normal speed
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
		running = false;
		speed = 3.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			// sets running to true if it is already past 5s after the last run
			if (!running && glfwGetTime() - runningEndTime >= 5.0f) {
				runningEndTime = 0;
				running = true;
				runningStartTime = glfwGetTime();
				speed = 8.0f;
			}

			// makes the player stop running after 3s
			else if (glfwGetTime() - runningStartTime >= 3.0f) {
				speed = 3.0f;
				runningEndTime = glfwGetTime();
			}
		}
	}

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
	cameraF = glm::normalize(direction);
}