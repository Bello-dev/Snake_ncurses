#ifndef HEADBE_H
#define HEADBE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>


#define WIDTHBE 40
#define HEIGHTBE 20
#define MAX_OBSTACLESBE 30

typedef struct {
    int xON, yON;
} PointON;

typedef struct NodeON {
    PointON positionON;
    struct NodeON *nextON;
} NodeON;

typedef struct {
    NodeON *headON;
    NodeON *tailON;
    int lengthON;
} SnakeON;

// Prototypes des fonctions
void initializeGameBE();
void generateFoodBE();
void generateObstaclesBE();
void displayBoardBE();
void moveSnakeBE();
void checkCollisionBE();
void freeSnakeBE();
int isPositionFreeBE(int xON, int yON);
void displayMenuBE();
void startGameBE();
void chooseLevelBE();
void printBorderBE();
void setupColorsBE();
void saveScoreBE();
void displayHighScoresBE();



#endif // ONDO JEAN KAREL 22U2381
