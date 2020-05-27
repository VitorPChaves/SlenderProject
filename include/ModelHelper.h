#pragma once
#include <Camera.h>
#include <Model.h>
#include <utility>
#include <assimp/include/Importer.hpp>
#include <assimp/include/scene.h>
#include <assimp/include/postprocess.h>

class ModelHelper{
public:


	static std::pair<glm::vec3,glm::vec3> createBox(vector<Vertex> vertices)
	{
		glm::vec3 min = glm::vec3(99999999999, 99999999999, 99999999999);
		glm::vec3 max = glm::vec3(-99999999999, -99999999999, -99999999999);
		for (unsigned int i = 0; i < vertices.size(); i++) {
			if (max.x < vertices[i].Position.x) {
				max.x = vertices[i].Position.x;
			}
			if (max.y < vertices[i].Position.y) {
				max.y = vertices[i].Position.y;
			}
			if (max.z < vertices[i].Position.z) {
				max.z = vertices[i].Position.z;
			}

			if (min.x > vertices[i].Position.x) {
				min.x = vertices[i].Position.x;
			}
			if (min.y > vertices[i].Position.y) {
				min.y = vertices[i].Position.y;
			}
			if (min.z > vertices[i].Position.z) {
				min.z = vertices[i].Position.z;
			}
		}
		return std::make_pair(min, max);
	}
};
