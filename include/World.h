#pragma once
#include <Camera.h>
#include <Model.h>
#include <CollidingManager.h>


class World {

	public:
		int forestSize = 50;
		int treeSpacing = 10;
		unsigned int texture;
		unsigned int VBO, VAO, EBO, diffuseMap, specularMap;
		std::unique_ptr<class Model> treeModel;

		World();
		~World();
		unsigned int initTextures(char const* path);
		void initBuffers();
		void transformGround(Shader* shader);
		void drawGround(Shader* shader);
		void transformTree(Shader* shader, int x, int z);
		void drawTrees(Shader& shader);

	private:
};