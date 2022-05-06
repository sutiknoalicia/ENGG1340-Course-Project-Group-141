//
// Created by sutik on 16/04/2022.
//

#include "shop.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>
#include <vector>
#include "mainStruct.h"
using namespace std;

// Item effects and price are subject to change
// still need to include add to inventory

void shop(Player &p, vector<Item> &inven, int &m, int i){
    Item weapon, potion, armor, bomb;
    Item special;
    int num, option=-1, cont =-1, ogLength = inven.size();
    int boost[3] = { 0, 5, 15 };
    int boostS[3] = { 0, 10, 20 };
    string stats[3] = { "HP", "Atk", "Def" };

    weapon={"WEAPON",{1, (15+boost[i]) },25};
    potion={"POTION",{0, (15+boost[i]) },25};
    armor={"ARMOR",{2, (15+boost[i]) },25};
    bomb={"BOMB",{3, (15+boost[i]) },25};

    // generates a number between 1-3, inclusive to determine item
    srand(time(0));
    num = (rand()%3)+1;
    switch (num){
        case 1:
            special={"WEAPON",{1, (20+boostS[i]) },100};
            break;
        case 2:
            special={"POTION",{0, (20+ boostS[i]) },100};
            break;
        case 3:
            special={"ARMOR",{2, (20+boostS[i]) },100};
            break;
    }

    cout << "Welcome to Amazon Prime!\n";
    cout << "ITEMS ON SALE\n";
    cout << "================================\n";

    while (option != 0 && cont != 0){
        cout << "[1] Very Standard Weapon\n";
        cout << "Description: Increases Player attack by " << (15+boost[i]) << " points\n";
        cout << "Price: " << weapon.price << endl;
        cout << " \n";
        cout << "[2] Very Standard Potion\n";
        cout << "Description: Restores Player HP by " << (15+boost[i]) << " points\n";
        cout << "Price: " << potion.price << endl;
        cout << " \n";
        cout << "[3] Very Standard Armor\n";
        cout << "Description: Increases Player defense by " << (15+boost[i]) << " points\n";
        cout << "Price: " << armor.price << endl;
        cout << " \n";
        cout << "[4] BOMB!\n";
        cout << "Description: Deals " << (15+boost[i]) << " damage points to the enemy\n";
        cout << "Price: " << bomb.price << endl;
        cout << " \n";
        cout << "[5] SPECIAL " << special.name << endl;
        cout << "Description: Increases Player " << stats[special.effect[0]] << " by " << special.effect[1] << " points\n";
        cout << "Price: " << special.price << endl;
        cout << " \n";
        cout << "[0] Exit\n";
        cout << "Funds: "<< p.money << endl;
        cout << "Which item would you like to buy? ";
        cin >> option;
        cout << endl;
        if (option != 0){
            switch (option){
                case 1:
                    if (p.money >= weapon.price){
                        p.money = p.money - weapon.price;
                        inven.push_back(weapon);
                        cout << "Remaining funds:" << p.money << " Gold\n";
                    }
                    else{
                        cout << "Insufficient funds!\n";
                    }
                    break;
                case 2:
                    if (p.money >= potion.price){
                        p.money = p.money - potion.price;
                        inven.push_back(potion);
                        cout << "Remaining funds:" << p.money << " Gold\n";
                    }
                    else{
                        cout << "Insufficient funds!\n";
                    }
                    break;
                case 3:
                    if (p.money >= armor.price){
                        p.money = p.money - armor.price;
                        inven.push_back(armor);
                        cout << "Remaining funds:" << p.money << " Gold\n";
                    }
                    else{
                        cout << "Insufficient funds!\n";
                    }
                    break;
                case 4:
                    if (p.money >= bomb.price){
                        p.money = p.money - bomb.price;
                        inven.push_back(bomb);
                        cout << "Remaining funds:" << p.money << " Gold\n";
                    }
                    else{
                        cout << "Insufficient funds!\n";
                    }
                    break;
                case 5:
                    if (p.money >= special.price){
                        p.money = p.money - special.price;
                        inven.push_back(special);
                        cout << "Remaining funds:" << p.money << " Gold\n";
                    }
                    else{
                        cout << "Insufficient funds!\n";
                    }
                    break;
            }
            cout << endl;
            cout << "Is there anything else?\n";
            cout << "Press 0 for 'No', 1 for 'Yes': ";
            cin >> cont;
            cout << endl;
            if (inven.size() != ogLength){
                m++;
            }
        }
    }
    cout << "Please come again!\n";
    cout << endl;
}