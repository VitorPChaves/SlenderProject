#pragma once
#include <CollidableBody.h>

class CollidingManager {
public:
	CollidingManager();
	void addBody(CollidableBody* newbody){
		bodies.push_back(newbody);
	}
	bool moveBodies() {
		for (int i = 0; i < bodies.size(); ++i) {
			auto body1 = bodies[i];

			for (int j = i+1; j < bodies.size(); ++j) {
				auto body2 = bodies[j];

				if (body1->isStatical() && body2->isStatical()) {
					continue;
				}

				auto lastPosition1 = body1->getPosition();
				auto lastPosition2 = body2->getPosition();

				//TODO

				if (intersection(*body1, *body2)) {

				}
			}
		}
	}
	bool intersection(CollidableBody& body1, CollidableBody& body2 ) {
		auto& a = body1.getBoundingBox();
		auto& b = body2.getBoundingBox();
		return(a.min.x <= b.max.x && a.max.x >= b.min.x) &&
		(a.min.y <= b.max.y && a.max.y >= b.min.y) &&
		(a.min.z <= b.max.z && a.max.z >= b.min.z);
	}
private:
	vector<CollidableBody*> bodies;
};