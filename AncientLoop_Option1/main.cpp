#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <cctype>
#include "battle.h"
#include "board.h"
#include "mainStruct.h"
#include "menu.h"
#include "saveload.h"
#include "shop.h"

using namespace std;

//stat descriptions
//HP    - Max damage an entity can take before dying
//Atk   - used to calculate how much damage an entity does
//Def   - used to calculate how much damage an entity resists (total damage = attack power of attacker - defense power of recipient)
//      - for enemies: how much XP they drop
//money - for players: how much gold the player has to buy items
//      - for enemies: how much gold they drop

//defining the player symbol
#define player    'P'
#define enemy     'E'
#define giant     'G'
#define bigsnake  'S'
#define dragon    'D'
//placeholder chest
#define chest     'O'

//players play on a 5x5 grid
char board[5][5] = { {'-', '-', '-', '-', '-'},
                     {'-', '-', '-', '-', '-'},
                     {'-', '-', player, '-', '-'},
                     {'-', '-', '-', '-', '-'},
                     {'-', '-', '-', '-', '-'} };

char bosses[3] = { 'G', 'S', 'D' };
string bossesName[3] = {"Giant", "Big Snake", "Dragon"};
string enemiesName[3] = {"Slime", "Skeleton", "Mage"};
string bossesSpAtk[3] = {"Stomp", "Constrict", "Flamethrower"};
int bossPos[2] = { 0, 2 };

int main(){
    //game instructions
    cout << "GAME INSTRUCTIONS\n";
    cout << "================================================\n";
    cout << "1. Press W, A, S, or D to move up, left, down or right, respectively\n";
    cout << "2. You can enter P or O to enter the Pause menu or Shop menu on every turn\n";
    cout << "3. Move towards an enemy, boss or chest to interact with them\n";
    cout << "4. For every game event, a prompt will be shown on the screen to help you input correctly. Please follow the prompts.\n";
    cout << endl;

    string name;
    cout << "What is your name? ";
    getline(cin, name);
    //initialise player base stats, numbers subject to change
    Player p = {name, 25, 20, 15, 0};
    int pX = 2, pY = 2;

    //initialise first boss (giant) base stats, numbers subject to change
    int bossBaseHP = 40, bossBaseAtk = 20, bossBaseDef = 15, bossBaseGold = 100, bossBaseSpAtk = 5;
    Enemy thisBoss = {"Giant", bossBaseHP, bossBaseAtk, bossBaseDef, bossBaseGold, true, "Stomp", 10};

    //initialise basic enemy stats, numbers subject to change
    int enemyBaseHP = 20, enemyBaseAtk = 15, enemyBaseDef = 8, enemyBaseGold = 10;
    
    int index = 0;
    initialiseBoard(board, index, bosses);

    int start = startMenu();
    if (start == 2){
        load(p, board);
        bool bossPosUpdate = false;
        //updating bosspos
        for (int i=0; i <5; i++){
            for (int j=0; j<5;j++){
                if (board[i][j] == 'G' || board[i][j] == 'S' || board[i][j] == 'D' ){
                    bossPos[0] = i;
                    bossPos[1] = j;
                    bossPosUpdate = true;
                    break;
                }
            }
            if (bossPosUpdate){
                break;
            }
        }
        bool playerPosUpdate = false;
        for (int i=0; i <5; i++){
            for (int j=0; j<5;j++){
                if (board[i][j] == 'P'){
                    pX = i;
                    pY = j;
                    playerPosUpdate = true;
                    break;
                }
            }
            if (playerPosUpdate){
                break;
            }
        }
    } else if (start == 3){
        p.HP = 0;
    }
    int moves = 1;

    while (!isDead(p.HP)){
        //spawns a new boss if the previous one gets killed

        if(isDead(thisBoss.HP)){
            index++;
            if (index == 3){
                break;
            }
            cout << "Congratulations! You cleared this board!" << endl;
            cout << "Moving to next board..." << endl;
            //resetting the board and player position
            for (int i = 0; i < 5; i++){
                for (int j = 0; j < 5; j++){
                   board[i][j] = '-';
                }
            }
            board[2][2] = player;
            pX = 2;
            pY = 2;
            //reinitialising the board
            initialiseBoard(board, index, bosses);
            string bName = bossesName[index];
            //changing the strength of bosses and enemies
            bossBaseHP += 20;
            bossBaseAtk += 10;
            bossBaseDef += 10;
            bossBaseGold += 100;
            string bSpAtk = bossesSpAtk[index];
            bossBaseSpAtk += 5;
            thisBoss = {bName, bossBaseHP, bossBaseAtk, bossBaseDef, bossBaseGold, true, bSpAtk, bossBaseSpAtk};
            bossPos[0] = 0;
            bossPos[1] = 2;
            enemyBaseHP += 10;
            enemyBaseAtk += 10;
            enemyBaseDef += 10;
            enemyBaseGold += 10;
        }

        printBoard(board);
        //accept player input
        string XY = acceptPlayerInput(board, pX, pY);
        if (XY[0] == 'P'){
            int choice = pauseMenu(p);
            switch (choice){
                case 2:
                    save(p, board);
                    cout << "Saved successfully!\n";
                    break;
                case 3:
                    save(p, board);
                    cout << "Saved successfully!\n";
                    p.HP = 0;
                    break;
            }
        } else if (XY[0] == 'I'){
            invenMenu(p, inven, moves);
        } else if (XY[0] == 'S'){
            shop(p, inven, moves, index);
        } else {
            board[pX][pY] = '-';

            pX = (int) XY[0] - (int) '0';
            pY = (int) XY[1] - (int) '0';

            if ((board[pX][pY] == 'G' || board[pX][pY] == 'S' || board[pX][pY] == 'D') && board[pX][pY] == board[bossPos[0]][bossPos[1]]){
                inBattle(p, thisBoss, inven, 'p', bossBaseHP);
                if (!isDead(p.HP)){
                    changeGold(p, thisBoss);
                    cout << endl << "Enemy defeated! " << p.name << " earned " << thisBoss.GoldDrop << " GOLD" << endl;
                } else {
                    endMenu();
                }
            } else if (board[pX][pY] == enemy){
                string eName = enemiesName[index];
                Enemy e = {eName, enemyBaseHP, enemyBaseAtk, enemyBaseDef, enemyBaseGold, false, "none", 0};
                inBattle(p, e, inven, 'p', enemyBaseHP);
                if (!isDead(p.HP)){
                    changeGold(p, e);
                    cout << endl << "Enemy defeated! " << p.name << " earned " << e.GoldDrop << " GOLD" << endl;
                } else {
                    endMenu();
                }
            } else if (board[pX][pY] == chest) {
                getChest(p, inven, index);
            }

            board[pX][pY] = player;
            moves++;
        }

        char event = changeBoard(board, moves, bossPos);
        if (event == 'b' && p.HP > 0){
            inBattle(p, thisBoss, inven, 'e', bossBaseHP);
            if (!isDead(p.HP)){
                changeGold(p, thisBoss);
                cout << endl << "Enemy defeated! " << p.name << " earned " << thisBoss.GoldDrop << " GOLD" << endl;
            } else {
                endMenu();
            }
        } else if (event == 'e'){
            string eName = enemiesName[index];
            Enemy e = {eName, enemyBaseHP, enemyBaseAtk, enemyBaseDef, enemyBaseGold, false, "none", 0};
            inBattle(p, e, inven, 'e', enemyBaseHP);
            if (!isDead(p.HP)){
                changeGold(p, e);
                cout << endl << "Enemy defeated! " << p.name << " earned " << e.GoldDrop << " GOLD" << endl;
            } else {
                endMenu();
            }
        }
    }

    if (index == 3) {
        winMenu();
    }

    return 0;
}