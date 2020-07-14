#include <Papers.h>

void Papers::initBuffers() {

	// Vertices defined for the texture image be applied

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.1f,  0.2f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.1f, -0.2f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.1f, -0.2f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.1f,  0.2f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	// Indices for the vertices texture image be applied

	int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Papers::collectClue(float pos, unsigned int func_vao, Camera* camera) {
	glm::vec3 position = glm::vec3(pos, 0.3f, 0.0f);

	if (glm::distance(camera->cameraP, position) <= 2.0f) {
		shouldDraw = false;
		//std::cout << "CLUE COLLECTED" << std::endl;
	}
}

float Papers::position() {
	srand(time(NULL));
	float pos = (rand() % 10);

	return pos;
}

void Papers::setShaderCharacteristics(Shader* paperShader, Camera* camera) {

	paperShader->use();

	//paperShader.setVec3("viewPos", camera->cameraP);
	paperShader->setVec3("viewPos", camera->cameraP);
	paperShader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	paperShader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	paperShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	paperShader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	paperShader->setFloat("material.shininess", 64.0f);
	paperShader->setInt("material.diffuse", 0);
}

void Papers::drawPapers(Shader* paperShader, Camera* camera, float xPosition) {

	collectClue(xPosition, VAO, camera);

	if (!shouldDraw) return;

	paperShader->use();

	camera->cameraProjection(paperShader);

	glm::mat4 model = glm::mat4(1.0f);
	model = translate(model, glm::vec3(xPosition, 0.3f, 0.0f));
	model = rotate(model, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0f));
	paperShader->setMat4("model", model);

	//bind diffuse map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
}