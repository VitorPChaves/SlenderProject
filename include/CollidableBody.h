#pragma once
#include <BoundingBox.h>

class CollidableBody {
public:
	CollidableBody(const CollidableBody&) = default;

	//@param _statical true if the object is statical false otherwise
	CollidableBody(BoundingBox& bbox, bool _statical) : bb(bbox) {
		position = bb.getCenter();
		statical = _statical;
	}
	glm::vec3 getPosition() {
		return position;
	}
	void setPosition(glm::vec3& newposition) {
		position = newposition;
	}
	glm::vec3 getMovement() {
		return movement;
	}
	void setMovement(glm::vec3& newmovement) {
		movement = newmovement;
	}
	BoundingBox getBoundingBox() {
		BoundingBox result = bb;
		result.min += position;
		result.max += position;
		return result;
	}

	bool isStatical() const { return statical; }
private:
	BoundingBox bb;
	glm::vec3 movement = glm::vec3(0);
	glm::vec3 position = glm::vec3(0);
	bool statical = true;
};