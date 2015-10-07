#pragma once
#include <GL\glew.h>
#include <SDL\SDL.h>
#include "Errors.h"
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>


#include "Shader.h"


class Primitives
{
public:
	Primitives();
	~Primitives();

	void createPrimitive();
	void createShaders();

	void drawShape(GLfloat deltaTime);
	void deleteShape();

	void loadImage();
	void updateCam(GLfloat deltaTime);

private:
	Shader _myShader;
	
	GLuint VBO[2], VAO[2];

	const Uint8* _currentKeyStates;

	GLfloat size = 1.0f;
	GLfloat *p_size = &size;

	unsigned int _screenWidth, _screenHeight;
	unsigned int *p_screenWidth = &_screenWidth;
	unsigned int *p_screenHeight = &_screenHeight;
	GLfloat ratio = 0.0f;
	GLfloat *p_ratio = &ratio;


	GLfloat timer = 0;
	GLfloat *p_timer = &timer;
private:
	//// VIEW /////
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;


private:
	//// CAMERA /////
	glm::vec3 cameraFront, cameraPos, cameraTarget, 
			  cameraDirection, up, cameraRight, cameraUp;

private:
	/// DELTA TIME ///
	GLfloat deltaTime = 0.0f;
	


private: 
	//// SHADER ////
	GLint modelLoc;
	GLint viewLoc;
	GLint projectLoc;


private:
	//// IMAGE ////
	int _width= NULL, _height = NULL;

	GLuint texture0, texture1;
	GLuint *tex0 = &texture0;
	GLuint *tex1 = &texture1;

	unsigned char *_image0 = nullptr;
	
private:
	//// Objects ////
	glm::vec3 cubePositions[5];

};

