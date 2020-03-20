#pragma once
#include<Light.h>
class Moonlight:public Light {
public:
	void lightImpact(Shader& shader, Camera& camera);
};