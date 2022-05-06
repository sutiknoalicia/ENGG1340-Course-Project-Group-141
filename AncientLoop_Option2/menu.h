//
// Created by sutik on 16/04/2022.
//

#ifndef ANCIENT_LOOP_MENU_H
#define ANCIENT_LOOP_MENU_H

#include <vector>
#include "mainStruct.h"

using namespace std;

int startMenu();
int pauseMenu(Player p);
char battleMenu(Player p, Enemy e, int eHP);
void invenMenu(Player &p, vector<Item> &inven, int &m);
void endMenu();
void winMenu();


#endif //ANCIENT_LOOP_MENU_H
