//
// Created by sutik on 16/04/2022.
//

#ifndef ANCIENT_LOOP_BATTLE_H
#define ANCIENT_LOOP_BATTLE_H

#include "mainStruct.h"
#include <vector>

extern int bossPos[2];

using namespace std;

bool turnOrder(char b[][5], int x, int y);
int calcDamge(int aatk, int ddef);
void changeGold(Player &p, Enemy &e);
bool isDead(int HP);
void getChest(Player &p, vector<Item> &inven, int i);
void useItem(Player &p, int i, vector<Item> &inven);
void useItemBattle(Player &p, int i, vector<Item> &inven, Enemy &e);
void printBattleScreen(Enemy e);
void inBattle(Player &p, Enemy &e, vector<Item> &inven, char first, int eHP);

#endif //ANCIENT_LOOP_BATTLE_H
