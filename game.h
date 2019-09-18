#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define UP 1 // defined constants for direction 
#define DOWN -1
#define RIGHT 2
#define LEFT -2
#define MAX 60

void initGrid(int x, int y);
void drawGrid();
void drawSnake();
void drawFood();

#endif //game_h included
