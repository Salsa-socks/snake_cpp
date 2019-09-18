#include <GL/gl.h>
#include <GL/glut.h>
#include "game.h"
#include <stdlib.h>
#include <stdio.h>

#define COLUMNS 40
#define ROWS 40
#define FPS 10

extern short sDirection;
bool gameOver = false;
int score = 0;

void keyboard_callback(int, int, int);
void timer_callback(int);

//to compile: gcc snake.cpp -o hw_opengl -lGL -lGLU -lglut
void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0); //RGBA values of screen default black, Alpha default 1
	initGrid(COLUMNS, ROWS);
}

void display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT); // we clear the color buffer , so that it is the color we specify
	drawGrid();
	drawSnake();
	drawFood();
	glutSwapBuffers();
	if (gameOver) //if game over is true
	{
		printf("Your score is: %d\n", score);
		printf("Game Over! YOU SUCK!\n");
//		notify-send(NULL, "Your Score", "GAME OVER, YOU SUCK", 0);
//		Messagebox(NULL, "Your Score: ", "GAME OVER, YOU SUCK", 0);
		exit(1);
	}
}

void reshape_callback(int w , int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //orthographic projection(x,y}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //ensures no changes are made to matrix at the start
	glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0); //x,y,near,far pts objects will be visible
	glMatrixMode(GL_MODELVIEW); //switch back to modelview matrix
}

int main (int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // dble buffer window - render 1, draw 2, swap
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Sssssnake");
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback); // called whenever window is created, resized or moved
	glutTimerFunc(0, timer_callback, 0);
	glutSpecialFunc(keyboard_callback);
	init();
	glutMainLoop();
	return (0);
}

void timer_callback(int)
{
	glutPostRedisplay();
	glutTimerFunc(500/FPS, timer_callback, 0);  // manually setting FPS-not exactly 10FPS but approx
}

void keyboard_callback(int key, int, int)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			if (sDirection != DOWN)
				sDirection = UP;
			break;
		case GLUT_KEY_DOWN:
			if (sDirection != UP)
				sDirection = DOWN;
			break;
		case GLUT_KEY_RIGHT:
			if (sDirection != LEFT)
				sDirection = RIGHT;
			break;
		case GLUT_KEY_LEFT:
			if (sDirection != RIGHT)
				sDirection = LEFT;
			break;
	}
}
