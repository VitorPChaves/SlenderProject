#pragma once
#include <Shader.h>
#include <Camera.h>
#include <Model.h>
#include <time.h>

class Slender {
public:
	std::unique_ptr<class Model> slenderModel;

	Slender();

	void slenderMechanics(Shader& slenderShader);

private:
	double timeElapsed();

	int position();

private:
	//this is the multiplier for slender appearence
	float i = 1;
	bool showSlender = false;
	float time_aux = 20;
};