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

	double timeElapsed();

	float position();

private:
	Camera* camera;

	bool showSlender = false;
	float time_aux = 10;
	//this is the multiplier for slender appearence
	float i = 1;

};