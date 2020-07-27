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
	Tree* tree = new Tree();
	
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
	paper_dont_look->diffuseMap = world->initTextures("../images/dont_look2.png");
	paper_he_can_see->diffuseMap = world->initTextures("../images/he_can_see2.png");

	vector<glm::vec3> treePositions = tree->getTreePositions();

	BoundingBox slenderBox(slender->slenderModel->meshes);
	CollidableBody slenderBody(slenderBox, false);
	collidingManager->addBody(&camera->cameraBody);

	tree->forEachTree([](CollidableBody& body) { collidingManager->addBody(&body); });

	glEnable(GL_DEPTH_TEST);

	glm::vec3 clue1 = tree->feedbackPaperPosition();
	glm::vec3 clue2 = tree->feedbackPaperPosition();
	glm::vec3 clue3 = tree->feedbackPaperPosition();

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

		tree->drawTrees(treeShader);
		
		// Paper

		paper->setShaderCharacteristics(&paperShader, camera);
		paper->drawPapers(&paperShader, camera, clue1);

		paper_dont_look->setShaderCharacteristics(&paperShader, camera);
		paper_dont_look->drawPapers(&paperShader, camera, clue2);

		paper_he_can_see->setShaderCharacteristics(&paperShader, camera);
		paper_he_can_see->drawPapers(&paperShader, camera, clue3);
		
		collidingManager->checkCollision();
		camera->input(window);
		collidingManager->moveBodies();

		// Slender
		slenderShader.use();
		camera->cameraProjection(&slenderShader);
		slenderShader.setVec3("viewPos", camera->cameraP);
		moonlight->lightImpact(slenderShader, *camera);
		flashlight->lightImpact(slenderShader, *camera);
		slender->slenderMechanics(slenderShader);

		cout << "-----------------" << endl;
		cout << "passou akeeeeeee" << endl;
		cout << "****************" << endl;
		
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