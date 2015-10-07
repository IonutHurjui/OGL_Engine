#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL\glew.h>

#include "Errors.h"


class Shader
{
public:
	Shader();
	~Shader();

	/* Compiles 2 shaders and links them to program ID */
	void compileShaders();
	/* Loads a shader from given file path and returns its contents as string */
	const std::string loadShader(const char* filePath);
	/* Tells OpenGL what programmed shader ID to use */
	void Use();
	/* Returns shader pointer when called */
	GLuint getSP(){ return *p_shaderID; }

private:

	GLuint shaderProgram;
	GLuint *p_shaderID = &shaderProgram;
};