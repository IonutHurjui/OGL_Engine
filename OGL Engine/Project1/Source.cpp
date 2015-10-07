//thecplusplusguy OpenGL tutorials
//Ported to SDL2 by DJCyberslash

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

float angle = 0.0;
const GLuint triangle = 1;

void DrawCube(float cubeSize)
{
	glBegin(GL_QUADS);
	//Front
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(cubeSize / 2, cubeSize / 2, cubeSize / 2);
	glVertex3f(-cubeSize / 2, cubeSize / 2, cubeSize / 2);
	glVertex3f(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);
	glVertex3f(cubeSize / 2, -cubeSize / 2, cubeSize / 2);

	//Left
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-cubeSize / 2, cubeSize / 2, cubeSize / 2);
	glVertex3f(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);
	glVertex3f(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
	glVertex3f(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);

	//Back
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(cubeSize / 2, cubeSize / 2, -cubeSize / 2);
	glVertex3f(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);
	glVertex3f(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
	glVertex3f(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);

	//Right
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(cubeSize / 2, cubeSize / 2, cubeSize / 2);
	glVertex3f(cubeSize / 2, cubeSize / 2, -cubeSize / 2);
	glVertex3f(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
	glVertex3f(cubeSize / 2, -cubeSize / 2, cubeSize / 2);

	//Top
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(-cubeSize / 2, cubeSize / 2, cubeSize / 2);
	glVertex3f(-cubeSize / 2, cubeSize / 2, -cubeSize / 2);
	glVertex3f(cubeSize / 2, cubeSize / 2, -cubeSize / 2);
	glVertex3f(cubeSize / 2, cubeSize / 2, cubeSize / 2);

	//Bottom
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-cubeSize / 2, -cubeSize / 2, cubeSize / 2);
	glVertex3f(-cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
	glVertex3f(cubeSize / 2, -cubeSize / 2, -cubeSize / 2);
	glVertex3f(cubeSize / 2, -cubeSize / 2, cubeSize / 2);

	glEnd();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 640.0 / 480.0, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}

void display()
{
	angle += 0.5;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(angle, 1.0, 1.0, 1.0);
	DrawCube(1.0);
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);
	init();
	bool running = true;
	Uint32 start;
	while (running)
	{
		start = SDL_GetTicks();
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					running = false;
					break;
				}

			}
		}
		if (angle>360)
			angle -= 360;
		display();
		SDL_GL_SwapWindow(window);
	}
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}