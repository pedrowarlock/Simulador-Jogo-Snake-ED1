#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "game.h"


void mainMenu(SnakeGame* snakeGame);
int choiceMenuItems();
void choiceObstacleItems(SnakeGame* snakeGame);
void choiceMenuSnakePosition(SnakeGame* snakeGame);
void cleamMenu();
void choiceMenuSimulator(SnakeGame* snakeGame);


#endif // MENU_H_INCLUDED
