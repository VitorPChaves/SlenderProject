#pragma once
#include <Shader.h>

class Papers {
public:
	unsigned int diffuseMap;

	void initBuffers();

	void drawPapers(Shader* paperShader);


private:
	unsigned int VBO, VAO, EBO;

	//const char* pathh = "C:/Users/luanb/source/repos/paper.png";
	//const char* pathh = "C:/Users/luanb/source/repos/dont_look.png";


};