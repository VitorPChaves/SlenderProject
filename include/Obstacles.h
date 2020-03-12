#pragma once

#include <Shader.h>
#include <Camera.h>

class Obstacles {
private:
	unsigned int VAO, VBO;
	unsigned int texture1;
	unsigned int texture2;

public:
	int i = 0;

	Obstacles();
	~Obstacles();

	glm::vec3 getCubePos(int i);

	void initTexture();

	void initBuffers();

	void drawStuff(Shader* shader, int i);
};



