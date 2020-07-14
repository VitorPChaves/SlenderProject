#pragma once
#include <Shader.h>
#include <time.h>
#include <camera.h>

class Papers {
public:
	unsigned int diffuseMap;

	void initBuffers();

	void setShaderCharacteristics(Shader* shader, Camera* camera);

	void drawPapers(Shader* paperShader, Camera* camera, float xPosition);

	float position();

	void collectClue(float pos, unsigned int vao, Camera* camera);

private:
	unsigned int VBO, VAO, EBO;
	bool shouldDraw = true;
};