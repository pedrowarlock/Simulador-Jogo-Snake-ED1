#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#include "game.h"
#include "menu.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    //SnakeGame *SnakeGame = malloc(sizeof(SnakeGame)); //Não ensinou malloc
    SnakeGame GS;
    SnakeGame* SnakeGame = NULL;
    SnakeGame = &GS;

    setBoardSize(SnakeGame, 10, 10);

    initItemObstacle(SnakeGame);
    initItemSnake(SnakeGame);
    resetWalkCount(SnakeGame);


    mainMenu(SnakeGame);
    return 0;
}
