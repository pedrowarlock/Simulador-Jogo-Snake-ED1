#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "game.h"
#include "menu.h"

int checkObstacleOnPosition(SnakeGame *snakeGame,  const int positionX, const int positionY)
{
    const int obstaclesLength = sizeof(snakeGame->obstacles) / sizeof(int);
    const int realPosition = getRealBoardPosition(snakeGame, positionX, positionY);

    int count;
    for (count = 0; count < obstaclesLength; count++)
    {
        if (snakeGame->obstacles[count] == realPosition)
        {
            return 1;
        }
    }
    return 0;
}


void initItemObstacle(SnakeGame *snakeGame)
{
    const int obstaclesLength = sizeof(snakeGame->obstacles) / sizeof(int);
    int count;
    for(count = 0; count < obstaclesLength; count++)
    {
        snakeGame->obstacles[count] = -1;
    }
}

void initItemSnake(SnakeGame *snakeGame)
{
    const int snakeLength = sizeof(snakeGame->snake) / sizeof(int);
    int count;
    for(count = 0; count < snakeLength; count++)
    {
        snakeGame->snake[count] = -1;
    }
}


void setSnakeToPosition(SnakeGame *snakeGame, const int boardX, const int boardY)
{
    const int snakeSize = sizeof(snakeGame->snake) / sizeof(int);
    int count;
    for(count = 0; count < snakeSize; count++)
    {
        snakeGame->snake[count] = getRealBoardPosition(snakeGame, boardX, boardY);
    }
    incrementWalkCount(snakeGame);
}


void setBoardSize(SnakeGame* snakeGame, const int boardX, const int boardY)
{
    snakeGame->gameSizeX = boardX;
    snakeGame->gameSizeY = boardY;
}


void setBoardObstacle(SnakeGame* snakeGame, const int boardX, const int boardY)
{
    const int obstaclePosition = getRealBoardPosition(snakeGame, boardX, boardY);
    const int obstacleSize = sizeof(snakeGame->obstacles) / sizeof(int);

    if (obstaclePosition > (snakeGame->gameSizeX * snakeGame->gameSizeY) || obstaclePosition < 0) return;


    int count;
    for (count=0; count< obstacleSize; count++)
    {
        if (snakeGame->obstacles[count] < 0)
        {
            snakeGame->obstacles[count] = obstaclePosition;
            return;
        }
    }
}


void drawBoardGame(SnakeGame* snakeGame)
{
    int getBoardItemSpace;
    const int gameSizeX = snakeGame->gameSizeX;
    const int gameSizeY = snakeGame->gameSizeY;

    printf("   |");

    int count;
    for (count=0; count < gameSizeY; count++)
    {
        printf("%d|",count + 1);
    }

    printf("\n");

    int countX, countY;
    for (countY = 0; countY < gameSizeY; countY++)
    {
        printf("%2d |",countY+1);
        for (countX = 0; countX < gameSizeX; countX++)
        {
            getBoardItemSpace = charItemOnSpace(snakeGame, countX, countY);
            drawObject(getBoardItemSpace); //if(getBoardItemSpace >= 0)
        }
        printf("\n");
    }
    printf("\n Blocos diferentes visitados: %d de %d (Uma vez por bloco, não acumula).\n", getWalkSnakeCount(snakeGame), gameSizeX * gameSizeY);
}


int charItemOnSpace(SnakeGame *snakeGame,const int boardX, const int boardY)
{
    int charItem;
    const int positionX = boardX+1;
    const int positionY = boardY+1;

    charItem = charObstaclePosition(snakeGame, positionX, positionY);
    if (charItem >= 0) return charItem;

    charItem = charPieceSnake(snakeGame, positionX, positionY);
    if (charItem >= 0) return charItem;

    return -1;
}


int charPieceSnake(SnakeGame * snakeGame, const int boardX, const int boardY)
{
    const int realPosition = getRealBoardPosition(snakeGame, boardX, boardY);
    const int snakeSize    = sizeof(snakeGame->snake) / sizeof(int);

    int count;
    for (count = 0; count < snakeSize; count++)
    {
        if (realPosition == snakeGame->snake[count])
        {
            if(count == 0) return HEAD;
            if(count  > 0 && count < snakeSize - 1) return BODY;
            if(count == snakeSize - 1) return TAIL;
        }
    }

    return -1;
}


int charObstaclePosition(SnakeGame * snakeGame, const int boardX, const int boardY)
{
    const int realPosition = getRealBoardPosition(snakeGame, boardX, boardY);
    const int obstacleSize = amountOfObstacles(snakeGame);

    int count;
    for (count = 0; count < obstacleSize; count++)
        if (realPosition == snakeGame->obstacles[count]) return OBSTACLE;

    return -1;
}


void drawObject(const SnakeObject part)
{
    switch (part)
    {
    case HEAD:
        printf("%c|", CHAR_HEAD);
        break;
    case BODY:
        printf("%c|", CHAR_BODY);
        break;
    case TAIL:
        printf("%c|", CHAR_TAIL);
        break;
    case OBSTACLE:
        printf("%c|", CHAR_OBS);
        break;
    default:
        printf("%c|", CHAR_SPACE);
    }
}


int simuleSnake(SnakeGame* snakeGame, const int randomMovAmounts)
{
    int count = 0;
    int struckCount = 0;

    while(count < randomMovAmounts)
    {

        if (moveSnakeToPosition(snakeGame, randomWalk()) == 0)
        {
            count += 1;
            cleamMenu();
            drawBoardGame(snakeGame);
            printf(" Etapa de simulação: %d de %d\n",count ,randomMovAmounts);
            sleep(2);
            struckCount = 0;
        }
        struckCount += 1;
        if(struckCount >= 100) return -1;
    }

    return 0;
}


int wallCollision(SnakeGame* snakeGame, const Direction snakeDirection)
{
    const int posX = snakeGame->gameSizeX;
    const int posY = snakeGame->gameSizeY;

    int count;

    switch (snakeDirection)
    {
    case UP:
        for(count = 0; count < posX; count++)
        {
            if (snakeGame->snake[0] == count+1) return 1;
        }
        break;
    case RIGHT:
        for(count = posX; count < posX * posY; count+= posX)
        {
            if (snakeGame->snake[0] == count) return 1;
        }
        break;
    case DOWN:
        for(count = posX*posY - (posX-1); count < posY*posX; count++)
        {
            if (snakeGame->snake[0] == count) return 1;
        }
        break;
    case LEFT:
        for(count = 0; count < posX*posY - (posX-1); count+= posX)
        {
            if (snakeGame->snake[0] == count + 1)   return 1;
        }
        break;
    }

    return 0;
}


int bodyCollision(SnakeGame* snakeGame, const Direction snakeDirection)
{
    const int destiniUp   = snakeGame->snake[0] - snakeGame->gameSizeX;
    const int destiniDown = snakeGame->snake[0] + snakeGame->gameSizeX;
    const int destiniLeft = snakeGame->snake[0] - 1;
    const int destiniRight= snakeGame->snake[0] + 1;

    const int snakeSize = sizeof(snakeGame->snake) / sizeof(int);

    int count, snakeBodyPosition;
    for(count = 0; count < snakeSize; count++)
    {
        snakeBodyPosition = snakeGame->snake[count];

        switch (snakeDirection)
        {
        case UP:
            if (destiniUp   == snakeBodyPosition) return 1;
            break;
        case RIGHT:
            if (destiniRight == snakeBodyPosition) return 1;
            break;
        case DOWN:
            if (destiniDown == snakeBodyPosition) return 1;
            break;
        case LEFT:
            if (destiniLeft == snakeBodyPosition) return 1;
            break;
        }
    }

    return 0;
}


int obstacleCollision(SnakeGame* snakeGame, const Direction snakeDirection)
{
    const int destiniUp   = snakeGame->snake[0] - snakeGame->gameSizeX;
    const int destiniDown = snakeGame->snake[0] + snakeGame->gameSizeX;
    const int destiniLeft = snakeGame->snake[0] - 1;
    const int destiniRight= snakeGame->snake[0] + 1;

    const int amountObstacles = amountOfObstacles(snakeGame);


    int count, obstaclePosition;
    for(count = 0; count < amountObstacles; count++)
    {
        obstaclePosition = snakeGame->obstacles[count];
        switch (snakeDirection)
        {
        case UP:
            if (destiniUp == obstaclePosition) return 1;
            break;
        case RIGHT:
            if (destiniRight == obstaclePosition) return 1;
            break;
        case DOWN:
            if (destiniDown == obstaclePosition) return 1;
            break;
        case LEFT:
            if (destiniLeft == obstaclePosition) return 1;
            break;
        }
    }

    return 0;
}

int snakeCollided(SnakeGame* snakeGame, const Direction snakeDirection)
{
    if(obstacleCollision(snakeGame, snakeDirection) == 1) return -1; //Colidiou com o obstaculo
    if(wallCollision(snakeGame, snakeDirection) == 1) return -2;     //Colidiou com a parede
    if(bodyCollision(snakeGame, snakeDirection) == 1) return -3;     //Colidiou com o proprio corpo

    return 0;
}


int moveSnakeToPosition(SnakeGame* snakeGame, const Direction snakeDirection)
{
    if (snakeCollided(snakeGame, snakeDirection) < 0) return -1;
    const int snakeSize = sizeof(snakeGame->snake) / sizeof(int);

    int count;
    for(count = snakeSize-1; count > 0; count--)
    {
        snakeGame->snake[count] = snakeGame->snake[count-1];
    }

    switch (snakeDirection)
    {
    case UP:
        snakeGame->snake[0] -= snakeGame->gameSizeX;
        break;
    case RIGHT:
        snakeGame->snake[0] = snakeGame->snake[0] + 1;
        break;
    case DOWN:
        snakeGame->snake[0] += snakeGame->gameSizeX;
        break;
    case LEFT:
        snakeGame->snake[0] = snakeGame->snake[0] - 1;
        break;
    }

    incrementWalkCount(snakeGame);

    return 0;
}



void resetWalkCount(SnakeGame * snakeGame)
{
    const int tabSize = snakeGame->gameSizeX * snakeGame->gameSizeY;

    int count;

    for(count = 0; count < tabSize; count++)
    {
        snakeGame->tabuleiro[0][count] = -1;

    }
}


void incrementWalkCount(SnakeGame * snakeGame)
{
    const int snakePositionX = getSnakePositionX(snakeGame);
    const int snakePositionY = getSnakePositionY(snakeGame);

    snakeGame->tabuleiro[snakePositionX-1][snakePositionY-1] = 1;
}


int getWalkSnakeCount(SnakeGame * snakeGame)
{
    const int tabSize = getBoardSizeX(snakeGame) * getBoardSizeY(snakeGame);
    int count, snakeWalk = 0;

    for(count = 0; count < tabSize; count++)
    {
        if (snakeGame->tabuleiro[0][count] >= 0)
        {
            snakeWalk++;
        }
    }
    return snakeWalk;
}


int getRealBoardPosition(SnakeGame * snakeGame, const int boardX, const int boardY)
{
    return (boardY * snakeGame->gameSizeX) - (snakeGame->gameSizeX - boardX);
}

int amountOfObstacles(SnakeGame* SnakeGame)
{
    int count = 0;
    while(SnakeGame->obstacles[count] != -1)
    {
        count++;
    }

    return count;
}


int randomWalk()
{
    return rand()% (DIRECTION_NUMBER) + 1;
}


int getBoardSizeX(SnakeGame* snakeGame)
{
    return snakeGame->gameSizeX;
}


int getBoardSizeY(SnakeGame* snakeGame)
{
    return snakeGame->gameSizeY;
}


int getSnakePositionX(SnakeGame* snakeGame)
{
    const int snakeRealPosition = snakeGame->snake[0];
    const int boardSizeX = getBoardSizeX(snakeGame);
    const int snakePositionY = getSnakePositionY(snakeGame);

    if (snakeRealPosition < 0) return -1;

    return boardSizeX - ((snakePositionY * boardSizeX) - snakeRealPosition);
}


int getSnakePositionY(SnakeGame* snakeGame)
{
    int boardSizeX = getBoardSizeX(snakeGame);
    int boardSizeY = getBoardSizeY(snakeGame);

    int snakeRealPosition = snakeGame->snake[0];//55
    if (snakeRealPosition < 0) return -1;

    int count, countLine = 0;
    for (count = 0; count < (boardSizeX * boardSizeY); count += boardSizeX, countLine++)
    {
        if (count > snakeRealPosition)
            break;
    }

    return countLine;
}

