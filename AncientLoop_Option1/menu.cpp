//
// Created by sutik on 16/04/2022.
//

#include "menu.h"
#include "mainStruct.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


int startMenu(){
    int option;
    fstream fin;
    string line;
    fin.open("start.txt");
    while (getline(fin,line)){
        cout << line << endl;
    }
    cout << endl;

    cout << "Welcome to Ancient Loop!\n";
    cout << "================================\n";
    cout << "[1] New game\n";
    cout << "[2] Load game\n";
    cout << "[3] Quit\n";
    cout << "Press 1, 2 or 3 to proceed: ";
    cin >> option;
    return option;
}

int pauseMenu(Player p){
    int option;
    cout << "GAME PAUSED\n";
    cout << "Stats:\n";
    cout << "HP: " << p.HP << endl;
    cout << "ATK: " << p.Atk << endl;
    cout << "DEF: " << p.Def << endl;
    cout << "GOLD: " << p.money << endl;
    cout << "================================\n";
    cout << "[1] Back to game\n";
    cout << "[2] Save\n";
    cout << "[3] Save and exit\n";
    cout << "Press 1, 2 or 3 to proceed: ";
    cin >> option;
    return option;
}

char battleMenu(Player p, Enemy e, int eHP){
    char option;
    cout << p.name << ": " << p.HP << "/" << "25" << endl;
    cout << e.name << ": " << e.HP << "/" << eHP << endl;
    cout << endl;
    cout << "BATTLE!\n";
    cout << "What will you do?\n";
    cout << "================================\n";
    cout << "[B] Battle\n";
    cout << "[I] Item\n";
    cout << "Enter your choice: ";
    cin >> option;
    option = toupper(option);
    while (option != 'B' && option != 'I'){
        cout << "Invalid choice, please reinput: ";
        cin >> option;
        option = toupper(option);
    }
    return option;
}

void invenMenu(Player &p, vector<Item> &inven, int &m){
    int baseAtk = 15, baseDef = 15;
    if (!inven.empty()){
        int option;
        int choice;
        cout << "INVENTORY\n";
        cout << "================================\n";
        //loop to traverse the vector
        for (int i = 0; i < inven.size(); i++){
            if (inven[i].effect[0] != 3){
                cout << i << " -> " << inven[i].name << ": " << inven[i].effect[1] << endl;
            }
        }
        cout << "Select item index: ";
        cin >> option;
        //error handling to ensure only valid item choices are made
        while (option < 0 || option >= inven.size()){
            cout << "Invalid choice, please reinput: ";
            cin >> option;
            if (option > 0 && option < inven.size()){
                if (inven[option].effect[0] == 3){
                    cout << "Bombs are unusable in the overworld, please reinput: " << endl;
                    cin >> option;
                }
            }
        }
        Item thisItem = inven[option];
        inven.erase(inven.begin()+option);

        switch (thisItem.effect[0]) {
            case 0:
                p.HP += thisItem.effect[1];
                if (p.HP > 25){
                    p.HP = 25;
                }
                break;
            case 1:
                p.Atk = (baseAtk + thisItem.effect[1]);
                break;
            case 2:
                p.Def = (baseDef + thisItem.effect[1]);
                break;
            default:
                break;
        }
        m++;
    } else {
        cout << "Your inventory is empty!\n";
    }
}

void endMenu(){
    fstream file;
    // creates new file called save.txt, overwrites progress
    file.open("save.txt",fstream::out);
    file.close();
    cout << endl;
    fstream fin;
    string line;
    fin.open("dead.txt");
    while (getline(fin,line)){
        cout << line << endl;
    }
}

void winMenu(){
    fstream fin;
    string line;
    fin.open("congrats.txt");
    while(getline(fin,line)){
        cout << line << endl;
    }
}
