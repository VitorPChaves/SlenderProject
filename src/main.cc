#include <Shader.h>
#include <Camera.h>
#include <Moonlight.h>
#include <Flashlight.h>
#include <World.h>
#include <Model.h>
#include <Texture.h>
#include <BoundingBox.h>
#include <CollidingManager.h>
#include <Papers.h>
#include <Slender.h>
#include <Tree.h>

GLFWwindow* window = nullptr;
Camera* camera = new Camera();
CollidingManager* collidingManager = new CollidingManager();

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

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_BLEND);// you enable blending function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;
}


int main() {

	if (!initGL()) {
		return -1;
	}

	Moonlight* moonlight = new Moonlight();
	Flashlight* flashlight = new Flashlight();
	World* world = new World();
	Papers* paper = new Papers();
	Slender* slender = new Slender();
	Tree* tree = new Tree();
	
	Shader groundShader("../shaders/defaultLightVS.txt", "../shaders/defaultLightFS.txt");
	Shader treeShader("../shaders/defaultLightVS.txt", "../shaders/defaultLightFS.txt");
	Shader paperShader("../shaders/vsPaperCoord.txt", "../shaders/fsPaperCoord.txt");
	Shader slenderShader("../shaders/vsSuit.txt", "../shaders/fsSuit.txt");

	world->initBuffers();
	paper->initBuffers();
	world->diffuseMap = world->initTextures("../images/ground3.jpg");
	world->specularMap = world->initTextures("../images/ground3.jpg");
	paper->diffuseMap = world->initTextures("../images/paper.png");
	vector<glm::vec3> treePositions = tree->getTreePositions();

	BoundingBox slenderBox(slender->slenderModel->meshes);
	CollidableBody slenderBody(slenderBox, false);
	collidingManager->addBody(&camera->cameraBody);

	tree->forEachTree([](CollidableBody& body) { collidingManager->addBody(&body); });

	glEnable(GL_DEPTH_TEST);

	do {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Ground
		groundShader.use();
		groundShader.setVec3("viewpos", camera->cameraP);
		groundShader.setFloat("material.shininess", 64.0f);
		camera->cameraProjection(&groundShader);
		moonlight->lightImpact(groundShader, *camera);
		flashlight->lightImpact(groundShader, *camera);
		world->drawGround(&groundShader);


		// Trees
		treeShader.use();
		treeShader.setVec3("viewpos", camera->cameraP);
		treeShader.setFloat("material.shininess", 32.0f);
		treeShader.setInt("material.diffuse", 0);
		camera->cameraProjection(&treeShader);
		moonlight->lightImpact(treeShader, *camera);
		flashlight->lightImpact(treeShader, *camera);
		tree->drawTrees(treeShader);
		
		// Paper
		paperShader.use();
		paperShader.setVec3("viewPos", camera->cameraP);
		paperShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		paperShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		paperShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		paperShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		paperShader.setFloat("material.shininess", 64.0f);
		paperShader.setInt("material.diffuse", 0);
		camera->cameraProjection(&paperShader);
		paper->drawPapers(&paperShader);

		
		collidingManager->checkCollision();
		camera->input(window);
		collidingManager->moveBodies();


		// Slender
		/*slenderShader.use();
		slenderShader.setVec3("viewPos", camera->cameraP);
		moonlight->lightImpact(slenderShader, *camera);
		flashlight->lightImpact(slenderShader, *camera);
		slender->slenderMechanics(slenderShader);*/

		
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window));

	world->~World();
	glDeleteProgram(groundShader.shaderProgram);
	glDeleteProgram(treeShader.shaderProgram);
	glDeleteProgram(slenderShader.shaderProgram);

	glfwTerminate();

	return 0;
}