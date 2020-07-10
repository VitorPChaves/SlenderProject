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

	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);

	glEnable(GL_BLEND);// you enable blending function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;
}

float position() {
	srand(time(NULL));
	float pos = (rand() % 3);

	return pos;
}

int main() {

	if (!initGL()) {
		return -1;
	}

	Moonlight* moonlight = new Moonlight();
	Flashlight* flashlight = new Flashlight();
	World* world = new World();
	Papers* paper = new Papers();
	Papers* paper_dont_look = new Papers();
	Papers* paper_he_can_see = new Papers();
	Slender* slender = new Slender();

	Shader groundShader("../shaders/defaultLightVS.txt", "../shaders/defaultLightFS.txt");
	Shader treeShader("../shaders/defaultLightVS.txt", "../shaders/defaultLightFS.txt");
	Shader paperShader("../shaders/vsPaperCoord.txt", "../shaders/fsPaperCoord.txt");
	Shader slenderShader("../shaders/vsSuit.txt", "../shaders/fsSuit.txt");

	world->initBuffers();
	paper->initBuffers();
	paper_dont_look->initBuffers();
	paper_he_can_see->initBuffers();

	world->diffuseMap = world->initTextures("../images/ground3.jpg");
	world->specularMap = world->initTextures("../images/ground3.jpg");
	paper->diffuseMap = world->initTextures("../images/paper.png");
	paper_dont_look->diffuseMap = world->initTextures("../images/dont_look.png");
	paper_he_can_see->diffuseMap = world->initTextures("../images/teste_scan.png");

	BoundingBox aa(slender->slenderModel->meshes);
	CollidableBody aabody(aa, false);
	collidingManager->addBody(&camera->cameraBody);
	collidingManager->addBody(&aabody);

	glEnable(GL_DEPTH_TEST);

	float xPosition = position();
	float xPosition2 = position();
	float xPosition3 = position();

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
		world->drawTrees(treeShader);
		//BoundingBox box(world->treeModel->meshes);
		//CollidableBody boxBody(box, true);
		//collidingManager.addBody(&boxBody);


		// Paper
		paper->setShaderCharacteristics(&paperShader, camera);
		paper->drawPapers(&paperShader, camera, xPosition);

		paper_dont_look->setShaderCharacteristics(&paperShader, camera);
		paper_dont_look->drawPapers(&paperShader, camera, xPosition2);

		paper_he_can_see->setShaderCharacteristics(&paperShader, camera);
		paper_he_can_see->drawPapers(&paperShader, camera, xPosition3);

		collidingManager->moveBodies();
		camera->input(window);

		// Slender
		slenderShader.use();
		camera->cameraProjection(&slenderShader);
		slenderShader.setVec3("viewPos", camera->cameraP);
		moonlight->lightImpact(slenderShader, *camera);
		flashlight->lightImpact(slenderShader, *camera);
		slender->slenderMechanics(slenderShader);

		/*cout << "passou akeeeeeee" << endl;
		cout << "passou akeeeeeee" << endl;
		cout << "passou akeeeeeee" << endl;*/

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