//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>
//
//#include "Obstacles.h"
//
//Obstacles::Obstacles()
//{ }
//
//Obstacles::~Obstacles() {
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//}
//
//void Obstacles::initTexture() {
//	glGenTextures(1, &texture1);
//	glBindTexture(GL_TEXTURE_2D, texture1);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	int width, height, nrChannels;
//
//	// Texture 1
//	unsigned char* data = stbi_load("C:/Users/vitor.patricio/Pictures/OpenGL/container.jpg", &width, &height, &nrChannels, 0);
//
//	if (data) {
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//		//std::cout << data << std::endl;
//
//
//	}
//	else {
//		std::cout << "ERROR LOADING TEXTURE!" << std::endl;
//	}
//
//	stbi_image_free(data);
//
//	glGenTextures(1, &texture2);
//	glBindTexture(GL_TEXTURE_2D, texture2);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	stbi_set_flip_vertically_on_load(true);
//
//
//	// Texture 2
//	data = stbi_load("C:/Users/vitor.patricio/Pictures/OpenGL/happyface.png", &width, &height, &nrChannels, 0);
//
//
//	if (data) {
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//		//std::cout << data << std::endl;
//
//		//glTexSubImage2D(GL_TEXTURE_2D, 0, -1, -1, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
//
//
//	}
//
//
//	else {
//		std::cout << "ERROR LOADING TEXTURE!" << std::endl;
//	}
//
//	stbi_image_free(data);
//}
//
//void Obstacles::initBuffers() {
//
//	float vertices[] = {
//			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//	};
//
//
//
//	//initBothBuffers(vertices, indices, 32, VAO1, VBO1, EBO);
//
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	//glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	//glEnableVertexAttribArray(2);
//
//	//glBindBuffer(GL_ARRAY_BUFFER, 0);
//	//glBindVertexArray(0);
//
//
//}
//
//glm::vec3 Obstacles::getCubePos(int i) {
//	glm::vec3 cubePositions[] = {
//		glm::vec3(0, -10, 0),
//		glm::vec3(0,  8, -10),
//		glm::vec3(0, -8, -10),
//		glm::vec3(0, 6, -20),
//		glm::vec3(0, -9, -20),
//		glm::vec3(0, 7, -30),
//		glm::vec3(0, -7, -30),
//		glm::vec3(0, 6, -40),
//		glm::vec3(0, -8, -40),
//		glm::vec3(0, 6, -50),
//		glm::vec3(0, -6, -50)
//	}; 
//	return cubePositions[i];
//}
//
//void Obstacles::drawStuff(Shader* shader, int i) {
//
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, texture1);
//
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, texture2);
//
//	glBindVertexArray(VAO);
//
//	for (i; i < 11; i++) {
//		glm::mat4 model = glm::mat4(1.0f);
//		//float angle = 50.0f * (i + 1);
//
//		model = glm::translate(model, getCubePos(i));
//		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//
//		shader->setMat4("model", model);
//
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//
//	}
//}