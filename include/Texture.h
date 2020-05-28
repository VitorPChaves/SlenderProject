#pragma once

//this header it's just to implement the buffers for the texture

#include <Shader.h>
#include <vector>
#include <cstdlib>

using namespace std;

class Text {
private:
	unsigned int vao;
	unsigned int texture;
	Shader& shaderProgram;
public:
	Text(Shader& shader);

	void Buffers(vector<float>& vertices, vector<int>& indices);

	void Bind();

	unsigned int TextureID(const char* path);
};