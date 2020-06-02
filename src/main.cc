//#define STB_IMAGE_IMPLEMENTATION

#include <Shader.h>
#include <Camera.h>
#include <Moonlight.h>
#include <Flashlight.h>
#include <Model.h>
#include <BoundingBox.h>
#include <CollidingManager.h>


GLFWwindow* window = nullptr;

Camera camera;
CollidingManager collidingManager;

unsigned int VAO, VBO, lightVAO, diffuseMap, specularMap, emissionMap;



void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	camera.mouse_callback(window, xpos, ypos);
}

unsigned int initTexture(char const* path) {
	unsigned int textureID;

	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);

	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	}
	else
	{
		std::cout << "ERROR LOADING PATH: " << path << std::endl;
	}

	stbi_image_free(data);


	return textureID;
}



bool initGL() {
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	window = glfwCreateWindow(1024, 768, "Audaces CG Internship Test", NULL, NULL);

	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not OpenGL 3.3 compatible.\n");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true; // http://glew.sourceforge.net/basic.html
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_BLEND);// you enable blending function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;
}


int main() {

	if (!initGL()) {
		return -1;
	}

	Moonlight moonlight = Moonlight();
	Flashlight flashlight = Flashlight();
	
	Shader lightingShader("../shaders/slenderman.vs.txt", "../shaders/slenderman.fs.txt");
	Shader myShader("../shaders/vsSuit.txt", "../shaders/fsSuit.txt");

	Model myModel("../images/scene.gltf");
	BoundingBox aa(myModel.meshes);
	CollidableBody aabody(aa, true);
	collidingManager.addBody(&camera.cameraBody);
	collidingManager.addBody(&aabody);

	glEnable(GL_DEPTH_TEST);

	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		myShader.use();
		myShader.setVec3("viewPos", camera.cameraP);
		
		moonlight.lightImpact(myShader, camera);
		flashlight.lightImpact(myShader, camera);
		
		collidingManager.moveBodies();
		camera.input(window);

		camera.transform(&myShader);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		myShader.setMat4("model", model);
		glEnable(GL_FRAMEBUFFER_SRGB);
		myModel.Draw(myShader);

		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window));

	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(myShader.shaderProgram);

	glfwTerminate();

	return 0;
}