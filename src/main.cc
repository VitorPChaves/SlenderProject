#include <Shader.h>
#include <Camera.h>
#include <Moonlight.h>
#include <Flashlight.h>
#include <World.h>
#include <Model.h>
#include <Texture.h>
#include <BoundingBox.h>
#include <CollidingManager.h>

//luan new


GLFWwindow* window = nullptr;
Camera* camera = new Camera();

CollidingManager collidingManager;


void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	camera->mouse_callback(window, xpos, ypos);
}

// LUAN
/*********************************
NAO PODE OLHAR PRA ELE
ELE APARECE CONFORME DETERMINADO EVENTO
	*DEPENDENDO DO TIPO DE PISTA, ELE APARECE E NÃO DEIXA PEGAR
OBVIO QUE VAI TER CRONOMETRO PRA ELE APARECER
	*MAS ELE APARECE CONFORME PISTAS VÃO SENDO COLETADAS
**********************************/

// (O IDEAL É QUE O MAIN NÃO TENHA METODOS/FUNÇÕES DESSE TIPO)
// (ELES PODEM SER COLOCADOS EM UM ARQUIVO OBJECTS.H E OBJECTS.CPP POR EXEMPLO / PODE INCLUIR SLENDER E PAPEL JUNTOS, SÓ PRA TIRAR DO MAIN MSM)

double timeElapsed() {
	return glfwGetTime();
}

// Vertices defined for the texture image be applied
vector<float> verticesPaper() {
	vector<float> _vertices = {
		// positions          // colors           // texture coords
		 0.1f,  0.2f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.1f, -0.2f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.1f, -0.2f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.1f,  0.2f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	return _vertices;
}

// Indices for the vertices texture image be applied
vector<int> indicesPaper() {
	vector<int> _indices = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	return _indices;
}

// FIM LUAN

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

// VITOR

	World* world = new World();
	world->initBuffers();

	Moonlight* moonlight = new Moonlight();
	Flashlight* flashlight = new Flashlight();
	Shader groundShader("../shaders/defaultLightVS.txt", "../shaders/defaultLightFS.txt");
	Shader treeShader("../shaders/defaultLightVS.txt", "../shaders/defaultLightFS.txt");

	world->diffuseMap = world->initTextures("../images/ground3.jpg");
	world->specularMap = world->initTextures("../images/ground3.jpg");

// FIM VITOR
// LUAN

	//Moonlight moonlight = Moonlight();
	//Flashlight flashlight = Flashlight();

	//shader relative to the paper
	Shader paperShader("../shaders/vsPaperCoord.txt", "../shaders/vsPaperCoord.txt");

	// (BOTAR TUDO NO INITBUFFERS())

	//vertices and indices receiving their coordinates 
	//by the functions at the top of the code
	vector<float> vertices = verticesPaper();
	vector<int> indices = indicesPaper();

	//texture object from the Texture class
	Text objText(paperShader);
	objText.Buffers(vertices, indices);
	objText.Bind();

	//importing the image from the directory and use him as a diffuse
	world->diffuseMap = objText.TextureID("C:/Users/luanb/source/repos/paper.png");

	// (ACHO MELHOR COLOCAR ESSAS VARIÁVEIS EM UM ARQUIVO SEPARADO JUNTO COM OS MÉTODOS LA DE CIMA)
	bool showSlender = false;
	float time_aux = 10;
	//this is the multiplier for slender appearence
	float i = 1;

	//const char* pathh = "C:/Users/luanb/source/repos/paper.png";
	//const char* pathh = "C:/Users/luanb/source/repos/dont_look.png";


	paperShader.use();
	paperShader.setInt("material.diffuse", 0);

	Shader myShader("../shaders/vsSuit.txt", "../shaders/fsSuit.txt");

	Model myModel("../images/scene.gltf");
	BoundingBox aa(myModel.meshes);
	CollidableBody aabody(aa, true);
	collidingManager.addBody(&camera->cameraBody);
	collidingManager.addBody(&aabody);

	glEnable(GL_DEPTH_TEST);

	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


// VITOR
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

// FIM VITOR
// LUAN

		/*----------LIGHTING PAPER-------------*/
		paperShader.use();
		paperShader.setVec3("viewPos", camera->cameraP);

		paperShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		paperShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		paperShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

		paperShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		paperShader.setFloat("material.shininess", 64.0f);

		// view/projection transformations
		paperShader.use();

		// (ISSO TUDO É IGUAL A camera->cameraProjection(&shader);)

		camera->cameraProjection(&paperShader);
		
		myShader.use();
		myShader.setVec3("viewPos", camera->cameraP);
		
		moonlight->lightImpact(myShader, *camera);
		flashlight->lightImpact(myShader, *camera);
		
		collidingManager.moveBodies();
		camera->input(window);

		// (DAQUI)

		// world transformation
		glm::mat4 model = glm::mat4(1.0f);

		paperShader.setMat4("model", model);

		// bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, world->diffuseMap);

		// render the paper
		paperShader.use();
		objText.Bind();
		//glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		// (ATÉ AQUI) (PODE SER UM METODO draw() EM UM ARQUIVO SEPARADO) (ESTÁ DESENHANDO OS PAPÉIS?)  


		// (INCLUIR NO MESMO ARQUIVO DOS MÉTODOS LA DE CIMA)

		/*----------SLENDER APPEARENCE-------------*/

		//CLASSE GAME SETTINGS
			//método APARIÇÃO SLENDER
			//

		//is used the time elapsed to count every second that 
			//slender will appear or not
		auto time = timeElapsed();
		
		cout << time << endl;

		//the slender will appear each "multiplier(i) * 10"
		if (time >= time_aux) {
			showSlender = !showSlender;
			i += 1.0;
			time_aux+= (i * 10);
			cout << "passs here" << endl;
			cout << "passs here" << endl;
			cout << "passs here" << endl;
		}

		if (showSlender) {
			myShader.use();

			camera->cameraProjection(&myShader);

			model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
			myShader.setMat4("model", model);
			glEnable(GL_FRAMEBUFFER_SRGB);
			myModel.Draw(myShader);
		}
// FIM LUAN

		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window));

	world->~World();
	glDeleteProgram(groundShader.shaderProgram);
	glDeleteProgram(treeShader.shaderProgram);
	glDeleteProgram(myShader.shaderProgram);

	glfwTerminate();

	return 0;
}