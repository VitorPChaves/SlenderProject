#pragma once
#include <Shader.h>
#include <CollidableBody.h>
#include <Camera.h>
#include <ProcessInput.h>

class Player {
public:
	CollidableBody playerBody;

	Player(Camera* camera, Input* key);
	~Player();
	void playerMovement();
	glm::vec3 getPlayerP();
	glm::vec3 getPlayerF();
	glm::vec3 getPlayerUp();
	CollidableBody getPlayerBody();

private:

	bool running = false;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	float speed = 3.0f;

	float runningStartTime = 0.0f;
	float runningEndTime = (float)glfwGetTime();

	Camera* camera;
	Input* key;

	void setPlayerBody(CollidableBody playerBody);

};