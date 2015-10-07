#pragma once
#include <GL\glew.h>
#include <SDL\SDL.h>
#include <stdio.h>
#include <iostream>
#include <string>


#include "Primitives.h"



enum class GameState {
	PLAY,
	EXIT,
	PAUSE
};




class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	void initSystem();
	inline void processInput();
	inline void gameLoop();
	inline void drawGame(GLfloat deltaTime);
	inline void handleInput(GLfloat deltaTime);

	SDL_Window* _window;
	SDL_GLContext _glContext;
	unsigned int _screenWidth;
	unsigned int _screenHeight;
	
	GameState _gameState;

	const Uint8* _currentKeyStates;

	Primitives triangle;


private:
	//// SETTINGS ////



};