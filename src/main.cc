#include <Shader.h>
#include <Camera.h>
#include <Moonlight.h>
#include <Flashlight.h>
#include <Model.h>
#include <Texture.h>
#include <gameSettings.h>


/*********************************
NAO PODE OLHAR PRA ELE
ELE APARECE CONFORME DETERMINADO EVENTO
	*DEPENDENDO DO TIPO DE PISTA, ELE APARECE E NÃO DEIXA PEGAR
OBVIO QUE VAI TER CRONOMETRO PRA ELE APARECER
	*MAS ELE APARECE CONFORME PISTAS VÃO SENDO COLETADAS
**********************************/

GLFWwindow* window = nullptr;

Camera camera;

unsigned int lightVAO, diffuseMap, specularMap, emissionMap;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

double timeElapsed() {
	return glfwGetTime();
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	camera.mouse_callback(window, xpos, ypos);
}

//vertices defined for the texture image be applied
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

//indices for the vertices texture image be applied
vector<int> indicesPaper() {
	vector<int> _indices = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	return _indices;
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


int main() {

	if (!initGL()) {
		return -1;
	}


	Moonlight moonlight = Moonlight();
	Flashlight flashlight = Flashlight();

	//shader relative to the paper
	Shader lightingShader("../shaders/vsPaperCoord.txt", "../shaders/vsPaperCoord.txt");

	//shader relative to the slender character 
	Shader myShader("../shaders/vsSuit.txt", "../shaders/fsSuit.txt");

	//vertices and indices receiving their coordinates 
		//by the functions at the top of the code
	vector<float> vertices = verticesPaper();
	vector<int> indices = indicesPaper();

	//texture object from the Texture class
	Text objText(lightingShader);
	objText.Buffers(vertices, indices);
	objText.Bind();

	//importing the image from the directory and use him as a diffuse
	diffuseMap = objText.TextureID("C:/Users/luanb/source/repos/paper.png");

	//load the character "slender" model 
	Model myModel("C:/Users/luanb/source/repos/steampunk_plague_doctor/scene.gltf");

	//bool showSlender = false;
	//float time_aux = 10;
	//this is the multiplier for slender appearence
	//float i = 1;

	//const char* pathh = "C:/Users/luanb/source/repos/paper.png";
	//const char* pathh = "C:/Users/luanb/source/repos/dont_look.png";


	lightingShader.use();
	lightingShader.setInt("material.diffuse", 0);

	gameSettings settings(myShader, camera, myModel);

	glEnable(GL_DEPTH_TEST);

	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.input(window);

		/*----------LIGHTING PAPER-------------*/
		lightingShader.use();
		lightingShader.setVec3("light.direction", lightPos);
		lightingShader.setVec3("viewPos", camera.cameraP);

		lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		lightingShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

		lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		lightingShader.setFloat("material.shininess", 64.0f);

		// view/projection transformations
		lightingShader.use();
		glm::mat4 projection = glm::perspective(glm::radians(camera.fov), 800.0f/600.0f, 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(camera.cameraP, camera.cameraP + camera.cameraF, camera.cameraUp);
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);

		// world transformation
		glm::mat4 model = glm::mat4(1.0f);
		lightingShader.setMat4("model", model);

		// bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);

		// render the paper
		lightingShader.use();
		objText.Bind();
		//glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		

		/*----------SLENDER APPEARENCE-------------*/

		//is used the time elapsed to count every second that 
			//slender will appear or not
		auto time = timeElapsed();
		
		cout << time << endl;

		settings.showSlender(time);

		//the slender will appear each "multiplier(i) * 10"
		/*if (time >= time_aux) {
			showSlender = !showSlender;
			i += 1.0;
			time_aux+= (i * 10);
			cout << "passs here" << endl;
			cout << "passs here" << endl;
			cout << "passs here" << endl;
		}

		if (showSlender) {
			myShader.use();

			camera.transform(&myShader);

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			myShader.setMat4("model", model);
			myModel.Draw(myShader);
		}*/

		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window));

	//glDeleteVertexArrays(1, &vao);
	glDeleteVertexArrays(1, &lightVAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteProgram(myShader.shaderProgram);
	//glDeleteProgram(lightingShader.shaderProgram);

	glfwTerminate();

	return 0;
}