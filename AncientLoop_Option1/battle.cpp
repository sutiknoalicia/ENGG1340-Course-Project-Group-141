#include "mainStruct.h"
#include "battle.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include "menu.h"
#include <time.h>

using namespace std;

//defining needed symbols
#define player    'P'
#define slime     "(  )"
#define goblin    "<.L.>"
#define evilhorse "<hn"
#define skeleton  "XmX"
#define mage      "*\\(*-*)"

const int playerBaseAtk = 5;
const int playerBaseDef = 5;
const int maxHP = 25;

//uses the board to check if a enemy approaches a player or vise versa
//returns false if an enemy approaches the player
//returns true if the player approaches an enemy
bool turnOrder(char b[][5], int x, int y){
    if (b[x][y] == player){
        return false;
    } else {
        return true;
    }
}

//aatk and adef refers to the Atk and Def stats of the attacking side
//ddef refers to the Def stat of the defending side
int calcDamge(int aatk, int ddef){
    //rounded down to avoid decimals
    int dmg = (aatk*aatk)/(4*ddef);

    //calculate critical hits (increases damage by 1.5x)
    //crits have a 5% (1/20) chance to occur
    srand(time(0));
    int crit = rand() % 20;
    if (crit == 0){
        dmg = dmg*1.5;
        cout << "Critical Hit!" << endl;
    }

    return dmg;
}

void changeGold(Player &p, Enemy &e){
    p.money += e.GoldDrop;
}

bool isDead(int HP){
    if (HP <= 0){
        return true;
    }
    return false;
}

void getChest(Player &p, vector<Item> &inven, int i){
    //powers of the items increase with the subsequent areas
    int powerBoost[3] = {0, 10, 15};
    //chests have a 50/50 chance to store item or gold
    srand(time(0));
    int isItem = rand() % 2;

    if (isItem == 0){
        //chests can store anywhere from 50 - 100 gold
        //numbers subject to change
        srand(time(0));
        int gold = rand() % 51 + 50;
        p.money += gold;
        cout << p.name << " found " << gold << " GOLD!" << endl;
    } else {
        string items[3] = {"POTION", "WEAPON", "ARMOR"};
        //randomly chooses between the 3 item types;
        srand(time(0));
        int item = rand() % 3;
        //randomly sets the "strength" of each item
        srand(time(0));
        int power = rand() % 6 + 10;
        Item thisItem = {items[item], {item, (power+powerBoost[i])}, 0};
        inven.push_back(thisItem);
        cout << items[item] << " (" << (power+powerBoost[i]) << ") added to inventory" << endl;
    }
}

void useItem(Player &p, int i, vector<Item> &inven){
    Item item = inven[i];
    //item is used up, so delete it from vector
    inven.erase(inven.begin() + i);

    switch (item.effect[0]){
        case 0:
            p.HP += item.effect[1];
            //ensures players wont overheal
            if (p.HP > maxHP){
                p.HP = maxHP;
            }
            break;
        case 1:
            //all weapons/armor only alter the player's base stats
            p.Atk = playerBaseAtk + item.effect[1];
            break;
        case 2:
            p.Def = playerBaseDef + item.effect[1];
            break;
    }
}

//players can only heal or use bombs in battle, and they can't sell items in battle, so the function is different from that of the overworld
void useItemBattle(Player &p, int i, vector<Item> &inven, Enemy &e){
    Item item = inven[i];
    inven.erase(inven.begin() + i);

    switch (item.effect[0]){
        case 0:
            p.HP += item.effect[1];
            //ensures players wont overheal
            if (p.HP > maxHP){
                p.HP = maxHP;
            }
            cout << "Player healed" << endl;
            break;
        case 3:
            //bombs do a fixed amount of damage
            e.HP -= 50;
            break;
            cout << "Player used a BOMB!" << endl;
        default:
            //if players pick an invalid item, they waste a turn
            cout << "You can't use this item in battle!" << endl;
    }
}

void printBattleScreen(Enemy e){
    //example battle screen: ☺     ❍
    if (!e.isBoss){
        cout << "(.V.)-|=>" <<  "    ";

        if (e.name == "Slime"){
            cout << slime << endl;
        } else if (e.name == "Goblin"){
            cout << goblin << endl;
        } else if (e.name == "Evil Horse"){
            cout << evilhorse << endl;
        } else if (e.name == "Skeleton"){
            cout << skeleton << endl;
        } else {
            cout << mage << endl;
        }
               
    } else {
        //bosses have a more detailed battle screen, stored in text files
        string filename;

        if (e.name == "Giant"){
            filename = "giant.txt";
        } else if (e.name == "Big Snake"){
            filename = "snake.txt";
        } else if (e.name == "Dragon"){
            filename = "dragon.txt";
        }

        ifstream fin;
        fin.open(filename);

        //handles failures in opening file
        if (fin.fail()){
            cout << "Error" << endl;
            exit(1);
        }

        string line;
        //output all lines
        while (getline(fin, line)){
            cout << line << endl;
        }

        //close the file
        fin.close();
    }
}

//first stores either 'e' or 'p' depending on wheter the enemy or player moves first, respectively
//returns true if player wins, false if they don't
void inBattle(Player &p, Enemy &e, vector<Item> &inven, char first, int eHP){
    bool boss = e.isBoss;
    printBattleScreen(e);

    while (!isDead(p.HP) && !isDead(e.HP)){
        int xtraAtk = 0;

        if (first == 'e'){
            if (boss){
                // the boss has a 1/3 chance to use its special move instead of its noraml attack
                srand(time(0));
                int special = rand() % 3;
                if (special == 0){
                    xtraAtk = e.SpAtk;
                    cout << e.name << " used " << e.SpAtkName << endl;
                }
            }
            int dmg = calcDamge((e.Atk+xtraAtk), p.Def);
            cout << e.name << " dealt " << dmg << " damage!" << endl;
            p.HP -= dmg;
        }
        if (!isDead(p.HP)){
            char menu = battleMenu(p, e, eHP);
            cout << endl;

            if (menu == 'B'){
                int dmg = calcDamge(p.Atk, e.Def);
                cout << p.name << " dealt " << dmg << " damage!" << endl;
                e.HP -= dmg;
            } else if (menu == 'I'){
                if (inven.size() == 0){
                    cout << "You have no items, you can only attack!" << endl;
                    int dmg = calcDamge(p.Atk, e.Def);
                    break;
                }
                for (int i = 0; i < inven.size(); i++){
                    cout << i << " -> " << inven[i].name << ": " << inven[i].effect[1] << endl;
                }
                cout << "Use which item? (input the index): ";
                int index;
                cin >> index;
                while (index < 0 || index >= inven.size()){
                    cout << "Invalid choice, please reinput: ";
                    cin >> index;
                }
                useItemBattle(p, index, inven, e);
            }
        }
        if (!isDead(e.HP)){
            if (first == 'p'){
                if (boss){
                    srand(time(0));
                    int special = rand() % 3;
                    if (special == 0){
                        xtraAtk = e.SpAtk;
                        cout << e.name << " used " << e.SpAtkName << endl;
                    }
                }
                int dmg = calcDamge((e.Atk+xtraAtk), p.Def);
                cout << e.name << " dealt " << dmg << " damage!" << endl;
                p.HP -= dmg;
            }
        }
    }
}