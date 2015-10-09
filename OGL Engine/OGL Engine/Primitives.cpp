#include "Primitives.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <assimp\Importer.hpp>




using namespace std;

using namespace glm;

const double PI = 3.14159265;

Primitives::Primitives()
{
	for (int i = 0; i < 2; i++){
		VAO[i] = NULL;
		VBO[i] = NULL;
 	}
	*p_screenWidth = 1400;
	*p_screenHeight = 800;
	GLfloat x, y;
	x = (GLfloat)*p_screenHeight;
	y = (GLfloat)*p_screenWidth;
	*p_ratio = y / x;
	/* CAMERA */
	cameraPos = vec3(0.0f, 0.0f, 6.0f);
	cameraFront = normalize(vec3(0.0f, 0.0f, -1.0f));
	cameraTarget = vec3(0.0f, 0.0f, 0.0f);
	up = vec3(0.0f, 1.0f, 0.0f);

	


	cubePositions[0] = { glm::vec3(0.0f, 0.0f, 0.0f) };
	cubePositions[1] = { glm::vec3(2.0f, 0.0f, 0.0f) };
	cubePositions[2] = { glm::vec3(-2.0f, 0.0f, 0.0f) };
	cubePositions[3] = { glm::vec3(0.0f, -5.0f, 0.0f) };
}

Primitives::~Primitives()
{
}

void Primitives::updateCam(GLfloat& deltaTime) {
	deltaTime /= 1000;

	cameraDirection = normalize(cameraPos - cameraTarget);
	cameraRight = normalize(cross(up, cameraDirection));
	cameraUp = normalize(cross(cameraDirection, cameraRight));

	_currentKeyStates = SDL_GetKeyboardState(NULL);

	GLfloat cameraSpeed = 2.0f * deltaTime;

	if (_currentKeyStates[SDL_SCANCODE_LSHIFT]) {
		cameraSpeed = 5.f * deltaTime;
	}
	if (_currentKeyStates[SDL_SCANCODE_W]) {
		cameraPos += cameraSpeed * cameraFront;
	}
	if (_currentKeyStates[SDL_SCANCODE_S]) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (_currentKeyStates[SDL_SCANCODE_A]) {
		cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (_currentKeyStates[SDL_SCANCODE_D]) {
		cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	
	
	
	
	

	if (firstInput) {
		lastX = *p_screenWidth/2;
		lastY = *p_screenHeight/2;
		firstInput = false;
	}
	
	
	SDL_GetMouseState(&xpos, &ypos);
	// mouse position offset between current and last frame
	GLfloat xOffset = xpos - lastX;
	GLfloat yOffset = lastY- ypos; // reversed since y coords are from bottom to top
	
	lastX = xpos;
	lastY = ypos;
	

	GLfloat sensitivity = 0.1f;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 80.0f) {
		pitch = 80.0f;
	}
	if (pitch < -80.0f) {
		pitch = -80.0f;
	}

	vec3 front;

	front.x = cos(radians(yaw))* cos(radians(pitch));
	front.y = sin(radians(pitch));
	front.z = sin(radians(yaw))*cos(radians(pitch));
	cameraFront = normalize(front);


}





void Primitives::drawShape(GLfloat& deltaTime){
	
	GLfloat radius = 6.0f;
	GLfloat camX = sin(size) * radius;
	GLfloat camz = cos(size) * radius;
	*p_timer = (GLfloat)SDL_GetTicks();

	GLfloat sinSize = sin(size);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *tex0);
	glUniform1i(glGetUniformLocation(_myShader.getSP(), "ourTexture0"), 0);
	
	_myShader.Use();

	view = lookAt(cameraPos,
				cameraPos+ cameraFront,
				cameraUp);
	
	projection = perspective(radians(75.0f), *p_ratio, 0.1f, 200.0f);

	modelLoc = glGetUniformLocation(_myShader.getSP(), "model");
	viewLoc = glGetUniformLocation(_myShader.getSP(), "view");
	projectLoc = glGetUniformLocation(_myShader.getSP(), "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(projectLoc, 1, GL_FALSE, value_ptr(projection));

	glBindVertexArray(VAO[0]);	

	// FIRST CUBE //

	GLfloat  angle = radians(10.0f);
	GLfloat test = (4 + sinSize)/4;

	model = translate(model, cubePositions[0]);
	model = scale(model, vec3(test, test, test));
	model = rotate(model, angle**p_size, vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = mat4();

	 // SECOND CUBE //
	
	model = translate(model, cubePositions[1]);
	model = scale(model, vec3(-test, -test, -test));
	model = rotate(model, angle**p_size, vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = mat4();

	// THIRD CUBE //
	model = translate(model, cubePositions[2]);
	model = scale(model, vec3(test*-1, test*-1 , test*-1));
	model = rotate(model, angle**p_size, vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = mat4();

	glBindTexture(GL_TEXTURE_2D, 0);

	////////////////////////////////////
	/* GROUND CUBE */

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *tex1);
	glUniform1i(glGetUniformLocation(_myShader.getSP(), "ourTexture1"), 1);

	model = translate(model, cubePositions[3]);
	model = scale(model, vec3(30.0f, 7.0f, 20.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = mat4();
	glBindTexture(GL_TEXTURE_2D, 0);

	////////////////////////////////////

	glBindVertexArray(0);
	
	*p_size +=  0.0025f*deltaTime ;

	
}


void Primitives::deleteShape(){
	glDeleteVertexArrays(1, &VAO[0]);
	glDeleteBuffers(1, &VBO[0]);
}


void Primitives::createPrimitive(){
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);


#pragma region CUBE

	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
	};

	

#pragma endregion  ///////////////////////////////

	/* VAO */
	
	glBindVertexArray(VAO[0]); /* USE before drawing obj */

			/* ANY FURTHER CALLS ON ARRAY BUFFER WILL AFFECT VBO UNTIL UNBOUND */
			glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
			/* COPY VERTICES DATA INTO ARRAY BUFFER(VBO) */
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

			//POSITION POINTER
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);

			//TEXTURE POINTER
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);

			glBindVertexArray(0);

}

void Primitives::createShaders(){

	_myShader.compileShaders();

}


void Primitives::loadImage(){
	//LoadTexture
	
	_image0 = stbi_load("Textures/face.png", &_width, &_height, 0, 3);

	if (_image0 == nullptr){
		fatalError("COULD NOT LOAD IMAGE");
	}

	glGenTextures(1, tex0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *tex0);

	//Generate texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _image0);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Set texture wrapping/filetering options on bound texObj
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	   //x
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);		//y

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// ANISOTROPY //
	/*GLfloat _value = 0.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &_value);*/
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8.0f);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(_image0);

	_image0 = nullptr;
	_width = NULL;
	_height = NULL;


	/* SECOND IMAGE */
	_image0 = stbi_load("Textures/wall.jpg", &_width, &_height, 0, 4);

	if (_image0 == nullptr){
		fatalError("COULD NOT LOAD IMAGE");
	}

	glGenTextures(1, tex1);
	glBindTexture(GL_TEXTURE_2D, *tex1);

	//Generate texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _image0);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Set texture wrapping/filetering options on bound texObj
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	   //x
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);		//y

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8.0f);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(_image0);

	_image0 = nullptr;
	_width = NULL;
	_height = NULL;

}

