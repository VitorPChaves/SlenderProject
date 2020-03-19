#pragma once
#include <Shader.h>
#include <Camera.h>
class Light {

	virtual void lightImpact(Shader& shader, Camera& camera) = 0;

};