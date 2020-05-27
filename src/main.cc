#define STB_IMAGE_IMPLEMENTATION

#include <Shader.h>
#include <Camera.h>
#include <stb_image.h>
#include <Moonlight.h>
#include <Flashlight.h>
#include <World.h>
#include <Model.h>

GLFWwindow* window = nullptr;
Camera* camera = new Camera();


void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	camera->mouse_callback(window, xpos, ypos);
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

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_BLEND);// you enable blending function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;
}
int main() {

	if (!initGL()) {
		return -1;
	}

	World* world = new World();
	world->initBuffers();

	Moonlight* moonlight = new Moonlight();
	Flashlight* flashlight = new Flashlight();
	Shader groundShader("../shaders/defaultLightVS.txt", "../shaders/defaultLightFS.txt");
	Shader treeShader("../shaders/defaultLightVS.txt", "../shaders/defaultLightFS.txt");


	world->diffuseMap = world->initTextures("../images/ground3.jpg");
	world->specularMap = world->initTextures("../images/ground3.jpg");

	glEnable(GL_DEPTH_TEST);

	do {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera->input(window);

		// Ground
		groundShader.use();
		groundShader.setVec3("viewpos", camera->cameraP);
		groundShader.setFloat("material.shininess", 64.0f);
		groundShader.setInt("material.diffuse", 0);
		groundShader.setInt("material.ambient", 0);
		camera->cameraProjection(&groundShader);
		moonlight->lightImpact(groundShader, *camera);
		flashlight->lightImpact(groundShader, *camera);
		world->drawGround(&groundShader);

		// Trees
		treeShader.use();
		treeShader.setVec3("viewpos", camera->cameraP);
		treeShader.setFloat("material.shininess", 32.0f);
		moonlight->lightImpact(treeShader, *camera);
		flashlight->lightImpact(treeShader, *camera);
		camera->cameraProjection(&treeShader);
		world->drawTrees(treeShader);

		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window));

	world->~World();
	glDeleteProgram(groundShader.shaderProgram);
	glDeleteProgram(treeShader.shaderProgram);

	glfwTerminate();

	return 0;
}