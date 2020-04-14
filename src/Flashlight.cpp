#include <Flashlight.h>

void Flashlight::lightImpact(Shader& shader, Camera& camera) {
	shader.setVec3("spotLight.position", camera.cameraP);
	shader.setVec3("spotLight.direction", camera.cameraF);
	shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(5.5f)));
	shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(8.75f)));


	shader.setVec3("SpotLight.ambient", 0.1f, 0.1f, 0.1f);
	shader.setVec3("spotLight.diffuse", 0.8f, 0.8f, 0.8f);
	shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("spotLight.constant", 1.0f);
	shader.setFloat("spotLight.linear", 0.09f);
	shader.setFloat("spotLight.quadratic", 0.032f);
}