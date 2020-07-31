#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
private:
	unsigned int shaderProgram;
public:
	GLint Result = GL_FALSE;
	int InfoLogLength = 0;

	// Reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentPath) {

		// [1] Retrieve the source code from the file
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// Ensure ifstream throws exceptions
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			// Open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// Reads buffers into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// Close files
			vShaderFile.close();
			fShaderFile.close();
			// Convert stream to string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			//std::cout << fragmentCode << std::endl;
		}
		catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		const char* vertexShaderSource = vertexCode.c_str();
		const char* fragmentShaderSource = fragmentCode.c_str();

		// [2] Compile Shaders
		int vertexShader, fragmentShader;

		// vertex shader
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);// checar erro

		// Check vertex shader for errors
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0)
		{
			char vertexError[1000];
			glGetShaderInfoLog(vertexShader, InfoLogLength, NULL, &vertexError[0]);
			std::cout << &vertexError[0];
		}

		// fragment Shader
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader); // checar

		// Check fragment shader for errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0)
		{
			char fragmentError[1000];
			glGetShaderInfoLog(fragmentShader, InfoLogLength, NULL,
				&fragmentError[0]);
			std::cout << &fragmentError[0];
		}

		// shader Program
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram); // checar

		//check program for errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &Result);
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0)
		{
			char programError[1000];
			glGetProgramInfoLog(shaderProgram, InfoLogLength, NULL, &programError[0]);
			std::cout << &programError[0];
		}
		
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
			
	}
	// Activate the shader
	void useShader() {
		glUseProgram(shaderProgram);
	}

	void setBool(const std::string &name, bool value) const {
		glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
	}
	void setInt(const std::string &name, int value) const {
		glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
	}
	void setFloat(const std::string &name, float value) const {
		glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
	}
	void setMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void setMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void setMat4(const std::string& name, glm::mat4 value) const {
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	void setVec3(const std::string& name, glm::vec3 value) const {
		glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), value.r, value.g, value.b);
	}
	void setVec3(const std::string& name, float x, float y, float z) const {
		glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
	}

	~Shader() {
		glDeleteShader(shaderProgram);
	}
};
#endif