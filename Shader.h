#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>


class MyShader
{
public:
	GLuint shaderProgram;

	MyShader(const char* vName, const char* fName) {
		//Loads the vertex and fragment shaders
		std::fstream vertSrc(vName);
		std::stringstream vertBuff;
		vertBuff << vertSrc.rdbuf();
		std::string vertS = vertBuff.str();
		const char* v = vertS.c_str();

		std::fstream fragSrc(fName);
		std::stringstream fragBuff;
		fragBuff << fragSrc.rdbuf();
		std::string fragS = fragBuff.str();
		const char* f = fragS.c_str();

		// Create vertex and fragment shaders 
		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertShader, 1, &v, NULL);
		glCompileShader(vertShader);

		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &f, NULL);
		glCompileShader(fragShader);

		shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vertShader);
		glAttachShader(shaderProgram, fragShader);
		glLinkProgram(shaderProgram);
	}

	// call glUseProgram() 
	void useProgram() {
		glUseProgram(shaderProgram);
	}

	
	GLuint getProgram() {
		return shaderProgram;
	}

	// set  vec3 variable in shader program 
	void setVec3(const GLchar* varName, glm::vec3 vec3) {
		unsigned int uniformLoc = glGetUniformLocation(shaderProgram, varName);

		glUniform3fv(uniformLoc, 1, glm::value_ptr(vec3));
	}

	// set  float variable in shader program */
	void setFloat(const GLchar* varName, float floatVal) {
		unsigned int uniformLoc = glGetUniformLocation(shaderProgram, varName);

		
		glUniform1f(uniformLoc, floatVal);
	}

	// set mat4 variable in shader program */
	void setMat4(const GLchar* varName, glm::mat4 mat4) {
		unsigned int uniformLoc = glGetUniformLocation(shaderProgram, varName);


		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE,
			glm::value_ptr(mat4));
	}

	// set Tex0 variable in shader program */
	void setTexture(const GLchar* varName, GLuint texture, GLint texIndex) {
		glActiveTexture(GL_TEXTURE0 + texIndex);
		GLuint texAddress = glGetUniformLocation(shaderProgram, varName);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(texAddress, texIndex);
	}

};

