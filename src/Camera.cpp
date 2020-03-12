#include <Camera.h>

void Camera::transform(Shader* shader) {

	shader->use();

	//const float radius = 10.0f;
	//float camX = sin(glfwGetTime()) * radius;
	//float camZ = cos(glfwGetTime()) * radius;

	//glm::mat4 projection = glm::mat4(1.0f);

	glm::mat4 view = glm::mat4(1.0f);
	//glm::vec3 cameraT = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::vec3 cameraD = glm::normalize(cameraP - cameraT);
	//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	//glm::vec3 cameraR = glm::normalize(glm::cross(up, cameraD));


	view = glm::lookAt(cameraP, cameraP + cameraF, cameraUp);
	//if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
	//	view = glm::translate(0.0f,-0.0)
	//}
	//view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
	//	glm::vec3(0.0f, 0.0f, 0.0f),
	//	glm::vec3(0.0f, 1.0f, 0.0f));
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
	glm::mat4 projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
	//view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));


	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
}