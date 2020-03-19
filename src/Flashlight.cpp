#include <Flashlight.h>

void Flashlight::lightImpact(Shader& shader, Camera& camera) {
	shader.use();
	shader.setVec3("light.position", camera.cameraP);
	shader.setVec3("light.direction", camera.cameraF);
	shader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
	shader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
	shader.setVec3("viewPos", camera.cameraP);

	shader.setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
	shader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
	shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("light.constant", 1.0f);
	shader.setFloat("light.linear", 0.09f);
	shader.setFloat("light.quadratic", 0.032f);
}