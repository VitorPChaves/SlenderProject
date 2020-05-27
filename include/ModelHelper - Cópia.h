#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utility>
#include <assimp/include/Importer.hpp>
#include <assimp/include/scene.h>
#include <assimp/include/postprocess.h>

class ModelHelper{
	static std::pair<glm::vec3,glm::vec3> createBox(aiMesh* mesh)
	{
		glm::vec3 min = glm::vec3(99999999999, 99999999999, 99999999999);
		glm::vec3 max = glm::vec3(-99999999999, -99999999999, -99999999999);
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			if (max.x > mesh->mVertices[i].x) {
				mesh->mVertices[i].x = max.x;
			}
			if (max.y > mesh->mVertices[i].y) {
				mesh->mVertices[i].x = max.x;
			}
			if (max.z > mesh->mVertices[i].z) {
				mesh->mVertices[i].z = max.z;
			}

			if (min.x < mesh->mVertices[i].x) {
				mesh->mVertices[i].x = min.x;
			}
			if (min.y < mesh->mVertices[i].y) {
				mesh->mVertices[i].x = min.x;
			}
			if (min.z < mesh->mVertices[i].z) {
				mesh->mVertices[i].z = min.z;
			}
		}
		return std::make_pair(min, max);
	}
};
