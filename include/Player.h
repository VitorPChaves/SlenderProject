#pragma once

#include <Shader.h>
#include "Camera.h"

class Player {
	Camera* camera;

public:
	Player(Camera* camera);

	void input(GLFWwindow* window);

	//void press_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
};