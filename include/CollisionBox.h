#pragma once
#include <Light.h>


class Flashlight: public Light {
public:
	void lightImpact(Shader& shader, Camera& camera);

};
