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

//bool endFlag = false;

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
		return false;
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

	Shader groundShader("../shaders/defaultLightVS.txt", "../shaders/defaultLightFS.txt");
	Shader treeShader("../shaders/defaultLightVS.txt", "../shaders/defaultLightFS.txt");
	Shader paperShader("../shaders/vsPaperCoord.txt", "../shaders/fsPaperCoord.txt");
	Shader paperShader2("../shaders/vsPaperCoord.txt", "../shaders/fsPaperCoord.txt");
	Shader paperShader3("../shaders/vsPaperCoord.txt", "../shaders/fsPaperCoord.txt");
	Shader slenderShader("../shaders/vsSuit.txt", "../shaders/fsSuit.txt");

	Moonlight* moonlight = new Moonlight();
	Flashlight* flashlight = new Flashlight();
	World* world = new World();
	Paper* paper = new Paper();
	Paper* paper_dont_look = new Paper();
	Paper* paper_he_can_see = new Paper();
	Slender* slender = new Slender();
	Tree* tree = new Tree();

	world->initBuffers();
	//paper->initBuffers();
	//paper_dont_look->initBuffers();
	//paper_he_can_see->initBuffers();

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

	glm::vec3 clue1 = tree->feedbackDrawPosition();
	glm::vec3 clue2 = tree->feedbackDrawPosition();
	glm::vec3 clue3 = tree->feedbackDrawPosition();

	bool endFlag;

	do {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		endFlag = paper->endProgram();

		// Ground
		groundShader.useShader();
		groundShader.setVec3("viewpos", camera->cameraP);
		groundShader.setFloat("material.shininess", 64.0f);
		camera->cameraProjection(&groundShader);
		moonlight->lightImpact(groundShader, *camera);
		flashlight->lightImpact(groundShader, *camera);
		world->drawGround(&groundShader);

		// Trees
		treeShader.useShader();
		treeShader.setVec3("viewpos", camera->cameraP);
		treeShader.setFloat("material.shininess", 32.0f);
		treeShader.setInt("material.diffuse", 0);
		camera->cameraProjection(&treeShader);
		moonlight->lightImpact(treeShader, *camera);
		flashlight->lightImpact(treeShader, *camera);

		world->drawTrees(treeShader);

		tree->drawTrees(treeShader);
		
		// Paper
		glm::vec3 variavelCamPos = glm::vec3(camera->cameraP.x, camera->cameraP.y, camera->cameraP.z);

		paper->setShaderCharacteristics(&paperShader, variavelCamPos);
		paper->undrawPaper(clue1, variavelCamPos);
		paper->drawPaper(&paperShader, camera, clue1);
		std::cout << "PAPER POS 1 = " << clue1.x << " " << clue1.y << " " << clue1.z << std::endl;

		paper_dont_look->setShaderCharacteristics(&paperShader2, variavelCamPos);
		paper_dont_look->undrawPaper(clue2, variavelCamPos);
		paper_dont_look->drawPaper(&paperShader2, camera, clue2);
		std::cout << "PAPER POS 2 = " << clue2.x << " " << clue2.y << " " << clue2.z << std::endl;

		paper_he_can_see->setShaderCharacteristics(&paperShader3, variavelCamPos);
		paper_he_can_see->undrawPaper(clue3, variavelCamPos);
		paper_he_can_see->drawPaper(&paperShader3, camera, clue3);
		std::cout << "PAPER POS 3 = " << clue3.x << " " << clue3.y << " " << clue3.z << std::endl;
		
		collidingManager->checkCollision();
		camera->input(window);
		collidingManager->moveBodies();

		// Slender
		slenderShader.useShader();
		slenderShader.setVec3("viewPos", camera->cameraP);
		camera->cameraProjection(&slenderShader);
		moonlight->lightImpact(slenderShader, *camera);
		flashlight->lightImpact(slenderShader, *camera);
		slender->slenderMechanics(slenderShader);

		cout << "Cam == " << camera->cameraP.x << " " << camera->cameraP.y << " " << camera->cameraP.z << endl;
		
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window));

	world->~World();
	paper->~Paper();

	glfwTerminate();

	return 0;
}