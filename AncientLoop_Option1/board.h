//
// Created by sutik on 16/04/2022.
//

#ifndef ANCIENT_LOOP_BOARD_H
#define ANCIENT_LOOP_BOARD_H

#include "mainStruct.h"
#include <string>

using namespace std;

void initialiseBoard(char (&b)[5][5], int index, char bs[3]);
void printBoard(char b[5][5]);
int countBlanks(char b[5][5], int (&s)[23][2]);
bool validMove(int x, int y);
bool startEvent(char b[5][5], int x, int y, char e);
void spawnChest(char (&b)[5][5]);
bool spawnEnemies(char (&b)[5][5]);
bool enemyMove(char (&b)[5][5], int x, int y, bool boss, int (&bp)[2]);
string acceptPlayerInput(char b[][5], int pX, int pY);
char changeBoard(char (&b)[5][5], int moves, int (&bp)[2]);

#endif //ANCIENT_LOOP_BOARD_H
