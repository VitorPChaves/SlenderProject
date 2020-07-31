#pragma once
#include <Shader.h>
#include <time.h>
#include <camera.h>

class Paper {
public:
	unsigned int diffuseMap;

	Paper() {
		initBuffers();
	}

	~Paper();

	//passar cm referencia a posicao
	void setShaderCharacteristics(Shader* shader, glm::vec3& varCameraPos);

	void drawPaper(Shader* paperShader, Camera* camera, glm::vec3& paperPos) const;

	//passar cm referencia a posicao
	void Paper::undrawPaper(const glm::vec3& pos, glm::vec3& _varCameraPos);

private:
	void initBuffers();

private:
	unsigned int VBO = 0, VAO = 0, EBO = 0;
	bool shouldDraw = true;
};