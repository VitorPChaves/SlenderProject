#pragma once

#include <Shader.h>
#include <Model.h>
#include <Camera.h>
#include <cstdlib>

class gameSettings {
private:
	int frequency = 10;
	int times = 1;
	Shader& shaderProgram;
	Camera& camera;
	Model& model;
public:
	gameSettings(Shader& shader, Camera& camera, Model& model);

	void showSlender(int time_elaps);

};

//a ideia eh passar o tempo de maquina como parametro e comparar com
	//a variavel dentro da propria classe
//colcoar todo aquele if dentro da classe