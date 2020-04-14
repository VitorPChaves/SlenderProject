#include<Moonlight.h>

void Moonlight::lightImpact(Shader& shader, Camera& camera) {
	shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	shader.setVec3("dirLight.diffuse", 0.05f, 0.05f, 0.05f);
	shader.setVec3("dirLight.specular", 0.15f, 0.15f, 0.15f);
}