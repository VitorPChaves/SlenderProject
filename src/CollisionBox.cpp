//#include "Player.h"
//
//Player::Player(Camera* camera)
//	: camera(camera)
//{ }
//
//void Player::input(GLFWwindow* window) {
//
//	float currentFrame = glfwGetTime();
//	const float cameraSpeed = 7.5f * camera->deltaTime;
//
//	camera->deltaTime = currentFrame - camera->lastFrame;
//	camera->lastFrame = currentFrame;
//
//
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera->cameraP += cameraSpeed * camera->cameraF;
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera->cameraP -= cameraSpeed * camera->cameraF;
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera->cameraP += glm::normalize(glm::cross(camera->cameraF, camera->cameraUp)) * cameraSpeed;
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera->cameraP -= glm::normalize(glm::cross(camera->cameraF, camera->cameraUp)) * cameraSpeed;
//
//	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
//		//camera->cameraP.y += 0.4f;
//
//		if (camera->cameraP.y <= 20.0f) {
//			camera->cameraP.y += 0.25f;
//
//		}
//		if (camera->cameraP.y >= 19.0f || (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)) {
//			camera->check = true;
//		}
//	}
//
//	if (camera->cameraP.y <= -20.0f) {
//		camera->check = false;
//	}
//
//	if (camera->check == true) {
//		if (camera->cameraP.z == 5.0f) {
//			camera->cameraP.y = 3.0f;
//		}
//		else {
//			camera->cameraP.y -= 0.1f;
//		}
//	}
//}
//
//void Player::press_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//
//
//	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
//		//camera->cameraP.y += 0.4f;
//
//		if (camera->cameraP.y <= 10.0f) {
//			camera->cameraP.y += 0.5f;
//
//		}
//		if (camera->cameraP.y >= 9.0f || (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)) {
//			camera->check = true;
//		}
//	}
//	if (camera->cameraP.y <= -10.0f) {
//		camera->check = false;
//	}
//
//	if (camera->check == true) {
//		camera->cameraP.y -= 0.2f;
//	}
//}
//
//void Player::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//
//	if (camera->firstMouse) {
//		camera->lastX = xpos;
//		camera->lastY = ypos;
//		camera->firstMouse = false;
//	}
//
//	float xOffset = xpos - camera->lastX;
//	float yOffset = camera->lastY - ypos;
//
//	camera->lastX = xpos;
//	camera->lastY = ypos;
//
//	const float sensitivity = 0.05f;
//	xOffset *= sensitivity;
//	yOffset *= sensitivity;
//
//	camera->yaw += xOffset;
//	camera->pitch += yOffset;
//
//	if (camera->pitch > 89.0f) {
//		camera->pitch = 89.0f;
//	}
//	if (camera->pitch < -89.0f) {
//		camera->pitch = -89.0f;
//	}
//
//
//	glm::vec3 direction;
//	direction.x = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
//	direction.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
//	direction.y = sin(glm::radians(camera->pitch));
//	camera->cameraF = glm::normalize(direction);
//}
//
//void Player::scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
//	if (camera->fov >= 1.0f && camera->fov <= 45.0f)
//		camera->fov -= yOffset;
//	else if (camera->fov <= 1.0f)
//		camera->fov = 1.0f;
//	else if (camera->fov >= 45.0f)
//		camera->fov = 45.0f;
//}
