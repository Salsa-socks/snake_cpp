#include "game.h"
#include <GL/glut.h>
#include <ctime>

int gridX, gridY;
bool food = true;
int snake_length = 5;
int foodX,foodY;
short sDirection = RIGHT;
extern bool gameOver;
extern int score;

int posX[60] = {20, 20, 20, 20, 20};
int posY[60] = {20, 19, 18, 17, 16}; //initial position of snake will be centre of the screen

void unit(int x, int y);
void random(int &x, int &y);

void initGrid(int x, int y)
{
	gridX = x;
	gridY = y;
}

void drawGrid()
{
	for (int x = 0; x < gridX; x++) //loop to draw grid 
	{
		for(int y = 0; y < gridY; y++)
		{
			unit(x, y);
		}
	}
}

void unit(int x, int y)
{
	if (x == 0 || y == 0 || x == gridX - 1 || y == gridY - 1)
	{
		glLineWidth(3.0); //loop to make edges red and inner grid white
		glColor3f(1.0, 0.0, 0.0);
	}
	else
	{
	glLineWidth(1.0);
	glColor3f(0.0, 0.0, 0.0); // line intensity (white)
	}

	glBegin(GL_LINE_LOOP);
		glVertex2f(x, y); //drawing a sqaure (x, y) 1unit in size
		glVertex2f(x + 1, y);
		glVertex2f(x +1, y + 1);
		glVertex2f(x, y + 1);
	glEnd();
}

void drawFood()
{
	if (food)
		random(foodX, foodY);
	food = false;
	glColor3f(1.0, 0.0, 1.0);
	glRectd(foodX,foodY, foodX + 1, foodY + 1);
}

void drawSnake()
{
	for (int i = snake_length - 1;i > 0; i--)
	{
		posX[i] = posX[i - 1];
		posY[i] = posY[i - 1];
	}
	if (sDirection == UP)      // loop through to auto move snake in pressed direction-pos ofheadblk
		posY[0]++;
	else if (sDirection == DOWN)
		posY[0]--;
	else if (sDirection == RIGHT)
		posX[0]++;
	else if (sDirection == LEFT)
		posX[0]--;

	for (int i = 0; i < snake_length; i++)
	{
		if (i == 0)
			glColor3f(0.0, 0.0, 1.0);
		else
			glColor3f(0.0, 1.0, 1.0);
		glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1);
	}
	if (posX[0] == 0 || posX[0] == gridX - 1 || posY[0] == 0 || posY[0] == gridY - 1)
		gameOver = true;
	if (posX[0] == foodX && posY[0] == foodY)
	{
		score++;
		snake_length++;
		if (snake_length > MAX)
			snake_length = MAX;
		food = true;

	}
}

void random(int &x, int &y)
{
	int _maxX = gridX - 2;
	int _maxY = gridY - 2;
	int _min = 1;
	srand(time(NULL));
	x = _min + rand() % (_maxX - _min);
	y = _min + rand() % (_maxY - _min);
}
