#include "MainGame.h"
#include "Errors.h"

using namespace std;



MainGame::MainGame()
{
	_window = nullptr;
	_glContext = nullptr;
	_screenWidth = 1600;
	_screenHeight = 1050;
	_gameState = GameState::PLAY;

};

MainGame::~MainGame()
{

};


void MainGame::run(){
	
	initSystem();
	
	triangle.createShaders();
	triangle.loadImage();
	triangle.createPrimitive();
	
	gameLoop();

};

////////////////// MAIN GAME LOOP ////////////////////

void MainGame::gameLoop(){
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;
	GLfloat currentFrame = 0.0f;

	while (_gameState != GameState::EXIT){
		currentFrame = static_cast<GLfloat>(SDL_GetTicks());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput();
		handleInput(deltaTime);

		//// DRAW STUFF /////
		drawGame(deltaTime);


		//// FPS LIMITER ////
		SDL_Delay(15);
	}
	triangle.deleteShape();

};
///////////////////////////////////////////////////////

void MainGame::drawGame(GLfloat deltaTime){
	//// CLEAR BACKGROUND COLOR ////
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	//// DRAW CODE HERE ////
	
	triangle.drawShape(deltaTime);




	//// SWAP Renderer Front and back buffers ////
	glFlush();
	SDL_GL_SwapWindow(_window);
}

///////////////////////////////////////////////////////

void MainGame::processInput(){
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)){
		switch (evnt.type)
		{
		case  SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		default:
			break;
		}
	}
};

void MainGame::handleInput(GLfloat deltaTime){
	_currentKeyStates = SDL_GetKeyboardState(NULL);
	triangle.updateCam(deltaTime);

	if (_currentKeyStates[SDL_SCANCODE_ESCAPE]){
		_gameState = GameState::EXIT;
		return;
	}
	if (_currentKeyStates[SDL_SCANCODE_F1]){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (_currentKeyStates[SDL_SCANCODE_F2]){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (_currentKeyStates[SDL_SCANCODE_F8]){
		glEnable(GL_MULTISAMPLE);
	}
	if (_currentKeyStates[SDL_SCANCODE_F7]){
		glDisable(GL_MULTISAMPLE);
	}
	
}

void MainGame::initSystem(){
	//////////////////////////////////////////////////////////////////////////
	//// INITIALIZE SDL ////
	printf("# Initializing SDL & Systems #\n");
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
		fatalError("SDL could not initialize.");
	}

	///////////////// SDL ATTRIBUTES ////////////////////////
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4 );
	
	//// CREATE A WINDOW ////
	_window = SDL_CreateWindow("OpenGL 4.5.0 Renderer/64-bit", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_RENDERER_PRESENTVSYNC);
	if (_window == nullptr){
		fatalError("SDL Window could not be created.");
	}

	SDL_SetWindowGrab(_window, SDL_TRUE);
	SDL_ShowCursor(SDL_DISABLE);
	//// CREATE THE CONTEXT ////
	_glContext = SDL_GL_CreateContext(_window);
	if (_glContext == nullptr){
		fatalError("SDL GL Context could not be created.");
	}

	//// INIT GLEW ////
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK){
		fatalError("GLEW could not be initialized.");
	}
	//// SET VIEWPORT ////
	glViewport(0, 0, _screenWidth, _screenHeight);


	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("# GPU Renderer: %s\n", renderer);
	printf("# OpenGL Version %s\n", version);

	//////////////////////////////////////////////////////////////////////////////////
	
};







