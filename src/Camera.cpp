#include <Camera.h>
#include <Windows.h>

Camera::Camera() : cameraBody(BoundingBox(glm::vec3(0), glm::vec3(0)), false) {}

void Camera::transform(Shader* shader) {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);

	view = glm::lookAt(cameraP, cameraP + cameraF, cameraUp);

	shader->use();
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
}

float Camera::startRun() {
	auto end = glfwGetTime();
	Sleep(10000);
	auto start = glfwGetTime();
	float time = start - end;
	return time;
}

float Camera::endRun() {
	auto start = glfwGetTime();
	Sleep(2000);
	auto end = glfwGetTime();
	float time = end - start;

	return time;
}


void Camera::input(GLFWwindow* window) {
	float currentFrame = glfwGetTime();
	float cameraSpeed = speed * deltaTime;

	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	cameraP = cameraBody.getPosition();
	cameraP.y = 0.0f;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraBody.setMovement(cameraSpeed * cameraF);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraBody.setMovement(-cameraSpeed * cameraF);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraBody.setMovement(glm::normalize(glm::cross(cameraF, cameraUp)) * cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraBody.setMovement(- glm::normalize(glm::cross(cameraF, cameraUp)) * cameraSpeed);


	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
		running = false;
		speed = 2.5f;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (!running && glfwGetTime() - runningEndTime >= 5.0f) {
			runningEndTime = 0;
			running = true;
			runningStartTime = glfwGetTime();
			speed = 10.0f;
		} 
		else if (glfwGetTime() - runningStartTime >= 1.0f) {
			speed = 2.5f;
			runningEndTime = glfwGetTime();
		}

	}



	//if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
	//	if (cameraF  20.0f) {
	//		cameraP.y += 0.1f;
	//	}
	//	if (cameraP.y >= 0.0f || (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)) {
	//		check = true;
	//	}
	//}

	//if (cameraP.y <= 0.0f) {
	//	check = false;
	//}

	//if (check == true) {
	//	cameraP.y -= 0.1f;

	//	if (cameraP.z == 5.0f) {
	//		cameraP.y = 3.0f;
	//	}
	//	else {
	//		cameraP.y -= 0.1f;
	//	}w
	//}

	//if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
	//	check = false;
	//}

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
	std::cout << cameraF.x << ' ' << cameraF.y << ' ' << cameraF.z << std::endl;
}

//void Camera::updateCameraVectors() {
//
//	// Calculate the new Front vector
//	glm::vec3 front;
//	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//	front.y = sin(glm::radians(pitch));
//	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//	cameraF = glm::normalize(front);
//
//	// Also re-calculate the Right and Up vector
//	cameraR = glm::normalize(glm::cross(cameraF, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
//	cameraUp = glm::normalize(glm::cross(cameraR, cameraF));
//}
//
//Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float Yaw, float Pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
//	Position = glm::vec3(posX, posY, posZ);
//	WorldUp = glm::vec3(upX, upY, upZ);
//	yaw = Yaw;
//	pitch = Pitch;
//	updateCameraVectors();
//}
//
//Camera::Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float Yaw = yaw, float Pitch = pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
//{
//	cameraP = position;
//	worldUp = up;
//	yaw = Yaw;
//	pitch = Pitch;
//	updateCameraVectors();
//}