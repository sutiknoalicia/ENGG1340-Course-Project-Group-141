//
// Created by sutik on 16/04/2022.
//

#ifndef ANCIENT_LOOP_MAINSTRUCT_H
#define ANCIENT_LOOP_MAINSTRUCT_H
#include <string>
#include <vector>

using namespace std;

//stat descriptions
//HP    - Max damage an entity can take before dying
//Atk   - used to calculate how much damage an entity does
//Def   - used to calculate how much damage an entity resists (total damage = attack power of attacker - defense power of recipient)
//      - for enemies: how much XP they drop
//money - for players: how much gold the player has to buy items
//      - for enemies: how much gold they drop

struct Player{
    string name;
    int HP;
    int Atk;
    int Def;
    int money;
};

struct Enemy{
    string name;
    int HP;
    int Atk;
    int Def;
    int GoldDrop;
    bool isBoss;
    string SpAtkName;
    int SpAtk;
};

//item pool:
//weapon - equipped by player to increase their attack power
//armor  - equipped by player to increase their defense power
//potion - consumable, increases player HP

struct Item{
    string name;
    //effect[0] stores what stat the item affects
    //effect[1] stores by how much the item affects the stat
    int effect[2];
    int price;
};

// inventory, need to fix
extern vector<Item> inven;

#endif //ANCIENT_LOOP_MAINSTRUCT_H
