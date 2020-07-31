#pragma once
#include <Shader.h>
#include <map>


class Input {

public:

	enum class Key {
		A,
		S,
		D,
		W,
		SPACE
	};

public:
	
	void processInput(GLFWwindow* window);

	bool isPressed(Key key);

	bool isReleased(Key key);

protected:

	std::map<Key, bool> _keysPressed;
	std::map<Key, bool> _keysReleased;

};