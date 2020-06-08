#include<Moonlight.h>

void Moonlight::lightImpact(Shader& shader, Camera& camera) {

	shader.setVec3("dirLight.direction", glm::normalize(glm::vec3(-0.2f, -1.0f, -0.3f)));
	shader.setVec3("dirLight.ambient", 0.02f, 0.02f, 0.02f);
	shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
}