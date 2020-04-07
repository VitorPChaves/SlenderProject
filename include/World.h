#include <Shader.h>
#include <Camera.h>

class World {

	public:
		Camera camera;
		unsigned int texture;
		unsigned int VBO, VAO, EBO;		

		unsigned int initTextures(char const* path);
		void initBuffers();
		void drawGround(Shader* shader);
		void transformGround(Shader* shader);
};