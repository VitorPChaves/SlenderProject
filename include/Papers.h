#pragma once
#include <Shader.h>
#include <time.h>
#include <camera.h>

class Papers {
public:
	unsigned int diffuseMap;

	void initBuffers();

	void setShaderCharacteristics(Shader* shader, Camera* camera);

	void drawPapers(Shader* paperShader, Camera* camera, glm::vec3& paperPos);

	float position();

	void collectClue(glm::vec3& pos, unsigned int vao, Camera* camera);

private:
	unsigned int VBO, VAO, EBO;
	bool shouldDraw = true;
};