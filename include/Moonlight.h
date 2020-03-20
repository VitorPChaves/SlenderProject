#pragma once
#include<Light.h>
class Moonlight:public Light {
	void lightImpact(Shader& shader, Camera& camera);
};