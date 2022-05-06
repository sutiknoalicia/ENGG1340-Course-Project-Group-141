//
// Created by sutik on 16/04/2022.
//

#ifndef ANCIENT_LOOP_SAVELOAD_H
#define ANCIENT_LOOP_SAVELOAD_H

#include "mainStruct.h"
#include "board.h"

using namespace std;

void save(Player p, char b[5][5]);
void load(Player &p, char (&b)[5][5]);

#endif //ANCIENT_LOOP_SAVELOAD_H
