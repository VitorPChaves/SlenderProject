#include <ProcessInput.h>

void Input::processInput(GLFWwindow* window) {

	_keysPressed[Input::Key::W] = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
	_keysReleased[Input::Key::W] = glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE;

	_keysPressed[Input::Key::A] = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
	_keysReleased[Input::Key::A] = glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE;

	_keysPressed[Input::Key::D] = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
	_keysReleased[Input::Key::D] = glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE;

	_keysPressed[Input::Key::S] = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
	_keysReleased[Input::Key::S] = glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE;

	_keysPressed[Input::Key::SPACE] = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
	_keysReleased[Input::Key::SPACE] = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE;
}

bool Input::isPressed(Key key) {
	return _keysPressed[key];
}

bool Input::isReleased(Key key) {
	return _keysReleased[key];
}