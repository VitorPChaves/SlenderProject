//#define STB_IMAGE_IMPLEMENTATION

#include <Shader.h>
#include <Camera.h>
//#include <stb_image.h>
#include <Moonlight.h>
#include <Flashlight.h>
#include <Model.h>


GLFWwindow* window = nullptr;

Camera camera;

unsigned int VAO, VBO, lightVAO, diffuseMap, specularMap, emissionMap;

//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


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

/*void initBuffers() {

	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}*/

//void drawLight(Shader* shader) {
//
//	lightPos.x = cos(glfwGetTime());
//	lightPos.y = cos(glfwGetTime());
//	lightPos.z = sin(glfwGetTime());
}

//void drawLight(Shader* shader) {
//
//	//lightPos.x = cos(glfwGetTime());
//	//lightPos.y = cos(glfwGetTime());
//	//lightPos.z = sin(glfwGetTime());
//
//	glm::mat4 model = glm::mat4(1.0f);
//
//	shader->use();
//
//	camera->transform(shader);
//
//	float angle = glm::radians(glfwGetTime());
//
//	model = glm::mat4(1.0f);
//	model = glm::translate(model, lightPos);
//	model = glm::scale(model, glm::vec3(0.2f));
//	model = glm::rotate(model, angle, lightPos);
//
//	shader->setMat4("model", model);
//
//	glBindVertexArray(lightVAO);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//}

//void drawCube(Shader* shader) {
//
//	glm::vec3 cubePositions[] = {
//	glm::vec3(0.0f,  0.0f,  0.0f),
//	glm::vec3(2.0f,  5.0f, -15.0f),
//	glm::vec3(-1.5f, -2.2f, -2.5f),
//	glm::vec3(-3.8f, -2.0f, -12.3f),
//	glm::vec3(2.4f, -0.4f, -3.5f),
//	glm::vec3(-1.7f,  3.0f, -7.5f),
//	glm::vec3(1.3f, -2.0f, -2.5f),
//	glm::vec3(1.5f,  2.0f, -2.5f),
//	glm::vec3(1.5f,  0.2f, -1.5f),
//	glm::vec3(-1.3f,  1.0f, -1.5f)
//	};
//
//	float time = glfwGetTime();
//
//	camera.transform(shader);
//
//	shader->use();
//	shader->setInt("material.diffuse", 0);
//	shader->setInt("material.specular", 1);
//	//shader->setInt("material.emission", 2);
//
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, diffuseMap);
//
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, specularMap);
//
//	//glActiveTexture(GL_TEXTURE2);
//	//glBindTexture(GL_TEXTURE_2D, emissionMap);
//
//	shader->setFloat("time", time);
//
//	for (unsigned int i = 0; i < 10; i++)
//	{
//		glm::mat4 model = glm::mat4(1.0f);
//		model = glm::translate(model, cubePositions[i]);
//		float angle = 20.0f * i;
//		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//		shader->setMat4("model", model);
//
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//	}
//}
//
//}
/*
void drawCube(Shader* shader) {

	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	float time = glfwGetTime();

	camera.transform(shader);

	shader->use();
	shader->setInt("material.diffuse", 0);
	shader->setInt("material.specular", 1);
	//shader->setInt("material.emission", 2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap);

	//glActiveTexture(GL_TEXTURE2);
	//glBindTexture(GL_TEXTURE_2D, emissionMap);

	shader->setFloat("time", time);

	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		shader->setMat4("model", model);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	
}*/

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

	std::cout << "asdasdasda" << std::endl;

	//initBuffers();
	//initBuffers();

	Moonlight moonlight = Moonlight();
	Flashlight flashlight = Flashlight();
	//Shader myShader("../shaders/vsCube.txt", "../shaders/fsCube.txt");
	//Shader lightingShader("../shaders/slenderman.vs.txt", "../shaders/slenderman.fs.txt");
	Shader myShader("../shaders/vsSuit.txt", "../shaders/fsSuit.txt");


	//diffuseMap = initTexture("../images/container2.png");
	//specularMap = initTexture("../images/container2_specular.png");

	//diffuseMap = initTexture("../images/container2.png");
	//specularMap = initTexture("../images/container2_specular.png");
	//emissionMap = initTexture("C:/Users/vitor.patricio/Pictures/OpenGL/matrix.jpg");

	//Model myModel("C:/Users/luanb/source/repos/nanosuit/nanosuit.obj");
	Model myModel("C:/Users/luanb/Downloads/14-runtime-callidus-v2/runtime/Libraries/Character/40K/officio assassinorum/callidus_v3.obj");

	glEnable(GL_DEPTH_TEST);

	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.input(window);

		//lightingShader.use();
		//lightingShader.setVec3("viewPos", camera.cameraP);
		//lightingShader.setFloat("material.shininess", 64.0f);
		//moonlight.lightImpact(lightingShader, camera);
		//flashlight.lightImpact(lightingShader, camera);

		//drawCube(&lightingShader);

		//lightingShader.use();
		//lightingShader.setVec3("viewPos", camera.cameraP);
		//lightingShader.setFloat("material.shininess", 64.0f);
		//moonlight.lightImpact(lightingShader, camera);
		//flashlight.lightImpact(lightingShader, camera);

		//drawCube(&lightingShader);

		//lightingShader.use();

		//drawLight(&lightingShader);

		myShader.use();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		myShader.setMat4("model", model);
		myModel.Draw(myShader);

		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window));

	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(myShader.shaderProgram);
	//glDeleteProgram(lightingShader.shaderProgram);

	glfwTerminate();

	return 0;
}