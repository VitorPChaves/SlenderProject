#pragma once
#include <CollidableBody.h>

class CollidingManager {
public:

	void addBody(CollidableBody* newbody){
		bodies.push_back(newbody);
	}

	void moveBodies() {
		for (int i = 0; i < bodies.size(); ++i) {
			auto body1 = bodies[i];

			for (int j = i+1; j < bodies.size(); ++j) {
				auto body2 = bodies[j];

				if (body1->isStatical() && body2->isStatical()) {
					continue;
				}

				auto lastPosition1 = body1->getPosition();
				auto lastPosition2 = body2->getPosition();

				body1->setPosition(body1->getPosition() + body1->getMovement());
				body2->setPosition(body2->getPosition() + body2->getMovement());

				if (intersection(*body1, *body2)) {
					body1->setPosition(lastPosition1);
					body2->setPosition(lastPosition2);
				}
			}
		}
	}

	bool intersection(const CollidableBody& body1, const CollidableBody& body2 ) {
		auto& a = body1.getBoundingBox();
		auto& b = body2.getBoundingBox();
		return(a.min.x <= b.max.x && a.max.x >= b.min.x) &&
		(a.min.y <= b.max.y && a.max.y >= b.min.y) &&
		(a.min.z <= b.max.z && a.max.z >= b.min.z);
	}

private:
	vector<CollidableBody*> bodies;
};