#pragma once
#include <Light.h>


class Flashlight: public Light {
	void lightImpact(Shader& shader, Camera& camera);

};
