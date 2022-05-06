//
// Created by sutik on 16/04/2022.
//

#include "mainStruct.h"
#include "saveload.h"
#include "board.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void save(Player p, char b[5][5]){
    fstream file;
    // creates new file called save.txt
    // saving to a file
    file.open("save.txt",fstream::out);
    file.close();

    ofstream fout;
    fout.open("save.txt");
    // write to save.txt the things that need to be saved
    // Player: HP, ATK, DEF, Gold, Inventory
    // Current playing board

    // Player Stats
    fout <<  p.HP << endl;
    fout << p.Atk << endl;
    fout << p.Def << endl;
    fout << p.money << endl;

    // Player Inventory
    fout << inven.size() << endl;
    for (int i=0; i < inven.size(); i++){
        fout << inven[i].name << endl;
        fout << inven[i].effect[0] << endl;
        fout << inven[i].effect[1] << endl;
        fout << inven[i].price << endl;
    }

    // Current playing board
    for (int i=0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            fout << b[i][j] << endl; // every element will be printed in a separate line
        }
    }

    fout.close();
}

void load(Player &p, char (&b)[5][5]){
    // loading from a file
    ifstream fin;
    fin.open("save.txt");
    int data, counter=0, invSize,invCounter1=0, boardIndex1 = 0, boardIndex2 = 0;
    string data1;
    string namedata;
    int effect0data, effect1data, pricedata;
    char data2;
    if (fin.tellg() != -1){
        while (!fin.fail()){
            // Player data
            if (invCounter1 == 4){
                invCounter1 = 0;
            }
            if (counter == 0){
                fin >> data;
                p.HP = data;
            }
            else if (counter == 1){
                fin >> data;
                p.Atk = data;
            }
            else if (counter == 2){
                fin >> data;
                p.Def = data;
            }
            else if (counter == 3){
                fin >> data;
                p.money = data;
            }
            else if (counter == 4){
                fin >> data;
                invSize = data; // inventory size
            }
                // Inventory Load
            else if ((4 < counter && counter <= 4+(invSize*4)) && invSize > 0){
                fin >> data1;
                switch (invCounter1){
                    case 0: // name
                        namedata = data1;
                        break;
                    case 1:
                        effect0data = stoi(data1);
                        break;
                    case 2:
                        effect1data = stoi(data1);
                        break;
                    case 3:
                        pricedata = stoi(data1);
                        break;
                }
                invCounter1 += 1;
                if (invCounter1 == 4){
                    Item thisItem = {namedata, {effect0data,effect1data},pricedata};
                    inven.push_back(thisItem);
                }
            }
                // Board Load
            else{
                fin >> data2;
                b[boardIndex1][boardIndex2] = data2;
                boardIndex2 += 1;
                if (boardIndex2 == 5){
                    boardIndex2 = 0;
                    boardIndex1 += 1;
                }
            }
            counter += 1;
        }
    } else {
        cout << "No save data detected, starting new game..." << endl;
    }
    fin.close();
}