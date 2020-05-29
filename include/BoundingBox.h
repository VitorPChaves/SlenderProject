#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utility>
#include <assimp/include/Importer.hpp>
#include <assimp/include/scene.h>
#include <assimp/include/postprocess.h>
#include <model.h>

class BoundingBox{
public:
	BoundingBox() = default;
	BoundingBox(const BoundingBox&) = default;

	BoundingBox(const glm::vec3& _min, const glm::vec3& _max) : min(_min), max(_max) {}

	BoundingBox (vector<Vertex>& vertices)
	{
		min = glm::vec3(99999999999, 99999999999, 99999999999);
		max = glm::vec3(-99999999999, -99999999999, -99999999999);
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
	}

	BoundingBox(vector<Mesh>& meshes) {
		BoundingBox sum;

		for (auto& mesh : meshes) {
			BoundingBox bb(mesh.vertices);
			sum = sum + bb;
		}

		min = sum.min;
		max = sum.max;
	}

	BoundingBox operator+(const BoundingBox& other) const {
		BoundingBox result;
		result.min.x = std::min(this->min.x, other.min.x);
		result.min.y = std::min(this->min.y, other.min.y);
		result.min.z = std::min(this->min.z, other.min.z);
		result.max.x = std::max(this->max.x, other.max.x);
		result.max.y = std::max(this->max.y, other.max.y);
		result.max.z = std::max(this->max.z, other.max.z);
		return result;
	}
	glm::vec3 getCenter() {
		return (min + max) / 2.0f;
	}
	glm::vec3 min = glm::vec3(0);
	glm::vec3 max = glm::vec3(0);
	
};
