#include <Player.h>
#include <Windows.h>

Player::Player(Camera* camera, Input* key) : playerBody(BoundingBox(glm::vec3(-0.15), glm::vec3(0.15)), false), camera(camera), key(key)
{
	playerBody.setPosition(getPlayerP());
}

Player::~Player() {
	
}

void Player::playerMovement() {
    float currentFrame = glfwGetTime();
    float cameraSpeed = speed * deltaTime;

    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glm::vec3 movDirection = glm::vec3(0);

    if (key->isPressed(Input::Key::W)) {
        movDirection += getPlayerF();
    }
    if (key->isPressed(Input::Key::S)) {
		movDirection -= getPlayerF();
    }
    if (key->isPressed(Input::Key::D)) {
		movDirection += glm::normalize(glm::cross(getPlayerF(), getPlayerUp()));
	}
    if (key->isPressed(Input::Key::A)) {
		movDirection -= glm::normalize(glm::cross(getPlayerF(), getPlayerUp()));
    }
    if (glm::length(movDirection) > 0)
        movDirection = glm::normalize(movDirection);

    playerBody.setMovement(movDirection * cameraSpeed);

    // sets running to false and returns to normal speed
    if (key->isReleased(Input::Key::SPACE)) {
        running = false;
        speed = 3.0f;
    }

    if (key->isPressed(Input::Key::W)) {

        if (key->isPressed(Input::Key::SPACE)) {
            // sets running to true if it is already past 5s after the last run
            if (!running && glfwGetTime() - runningEndTime >= 5.0f) {
                runningEndTime = 0;
                running = true;
                runningStartTime = glfwGetTime();
                speed = 8.0f;
            }

            // makes the player stop running after 3s
            else if (glfwGetTime() - runningStartTime >= 3.0f) {
                speed = 3.0f;
                runningEndTime = glfwGetTime();
            }
        }

    }
    camera->setCameraP(playerBody.getPosition());
}


glm::vec3 Player::getPlayerP() {
	return camera->getCameraP();
}

glm::vec3 Player::getPlayerF() {
	return camera->getCameraF();
}

glm::vec3 Player::getPlayerUp() {
	return camera->getCameraUp();
}

void Player::setPlayerBody(CollidableBody playerBody) {
	this->playerBody = playerBody;
}

CollidableBody Player::getPlayerBody() {
	return playerBody;
}