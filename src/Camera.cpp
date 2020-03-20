#include <Camera.h>



void Camera::transform(Shader* shader) {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
	view = glm::lookAt(cameraP, cameraP + cameraF, cameraUp);
	shader->use();
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
}

void Camera::input(GLFWwindow* window) {
	float currentFrame = glfwGetTime();
	const float cameraSpeed = 7.5f * deltaTime;

	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraP += cameraSpeed * cameraF;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraP -= cameraSpeed * cameraF;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraP += glm::normalize(glm::cross(cameraF, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraP -= glm::normalize(glm::cross(cameraF, cameraUp)) * cameraSpeed;



	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (cameraP.y <= 20.0f) {
			cameraP.y += 0.25f;
		}
		if (cameraP.y >= 19.0f || (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)) {
			check = true;
		}
	}
	if (cameraP.y <= -20.0f) {
		check = false;
	}
	if (check == true) {
		if (cameraP.z == 5.0f) {
			cameraP.y = 3.0f;
		}
		else {
			cameraP.y -= 0.1f;
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