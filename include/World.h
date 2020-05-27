#include <Shader.h>
#include <Camera.h>

class World {

	public:
		int forestSize = 50;
		int treeSpacing = 10;
		unsigned int texture;
		unsigned int VBO, VAO, EBO, diffuseMap, specularMap;

		World();
		~World();
		unsigned int initTextures(char const* path);
		void initBuffers();
		void transformGround(Shader* shader);
		void drawGround(Shader* shader);
		void transformTree(Shader* shader, int x, int z);
		void drawTrees(Shader& shader);

	private:
		std::unique_ptr<class Model> treeModel;
};