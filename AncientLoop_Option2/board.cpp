#include "board.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <cctype>
#include <time.h>

using namespace std;

//defining the characters representing each entity on the overworld
#define player    'P'
#define enemy     'E'
#define slime     "(  )"
#define goblin    "<.L.>"
#define evilhorse "<hn"
#define skeleton  "XmX"
#define mage      "*\\(*-*)"
#define giant     'G'
#define bigsnake  'S'
#define dragon    'D'
#define chest     'O'

//array to store the position of all blank spaces
//the max amount of blank spaces is 23, since 1 space will always be the player, and another space will always be the boss
int allBlankSpace[23][2];

void initialiseBoard(char (&b)[5][5], int index, char bs[3]){
    //spawns the area's boss at the top centre of the grid
    b[0][2] = bs[index];
    //every new area starts with one enemy spawned
    srand(time(0));
    int randX = rand() % 4;
    srand(time(0));
    int randY = rand() % 4;

    //condition to check if enemy spawns in player's or boss' position
    while ((randX == 2 && randY == 2) || (randX == 0 && randY == 2)){
        //gives them a new position
        srand(time(0));
        int randX = rand() % 4;
        srand(time(0));
        int randY = rand() % 4;
    }

    b[randX][randY] = enemy;
}

void printBoard(char b[5][5]){
    cout << endl;
    for (int i = 0; i < 5; i ++){
        for (int j = 0; j < 5; j++){
            cout << b[i][j] << " ";
        }
        cout << endl;
    }
}

//counts and returns the number of blank ('-') spaces
//also updates the allBlankSpace array
int countBlanks(char b[5][5], int (&s)[23][2]){
    int index = 0;
    for (int i = 0; i < 5; i ++){
        for (int j = 0; j < 5; j++){
            if (b[i][j] == '-'){
                s[index][0] = i;
                s[index][1] = j;
                index++;
            }
        }
    }
    return index;
}

//checks if an entity is within the boundaries of the map
bool validMove(int x, int y){
    if (x < 0 || x > 4){
        return false;
    }
    if (y < 0 || y > 4){
        return false;
    }
    return true;
}

//checks if player and enemy/boss collide, starting battle
bool startEvent(char b[5][5], int x, int y, char e){
    //players can interact with anything
    if (e == player && (b[x][y] == enemy || b[x][y] == giant || b[x][y] == bigsnake || b[x][y] == dragon || b[x][y] == chest)){
        return true;
    //enemies and bosses only interact with players
    } else if (e != player && b[x][y] == player){
        return true;
    }
    return false;
}

bool spawnEnemies(char (&b)[5][5]){
    //each turn, an enemy has a 1/3 chance to spawn
    srand(time(0));
    int spawn = rand() % 3;
    int count = countBlanks(b, allBlankSpace);

    if (spawn == 0){
        //same logic as spawn enemies
        srand(time(0));
        if (count > 0){
            int index = rand() % count; 
            b[allBlankSpace[index][0]][allBlankSpace[index][1]] = enemy;
        }
        return true;
    }
    return false;
}

void spawnChest(char (&b)[5][5]){
    //each turn, a chest has a 1/10 chance to spawn
    //chests can only spawn if enemies don't spawn
    //enemies have a 2/3 chance to not spawn
    //so to make the chance 1/10, within this function, chests need a 3/20 chance to spawn
    srand(time(0));
    int spawn = rand() % 20;
    int count = countBlanks(b, allBlankSpace);

    if (spawn == 0 || spawn == 1 || spawn == 2){
        srand(time(0));
        if (count > 0){
            //randomly picks a blank space
            int index = rand() % count;
            b[allBlankSpace[index][0]][allBlankSpace[index][1]] = chest;
        }
    }
}

bool enemyMove(char (&b)[5][5], int x, int y, bool boss, int (&bp)[2]){
    //50/50 chance to move in the x- or y-axis
    int ogX = x, ogY = y;
    char thisEntity = b[x][y];
    srand(time(0));
    int XorY = rand() % 2;
    bool moved = false;

    if (XorY == 0){
        //50/50 chance to move lup or down
        srand(time(0));
        int UorD = rand() % 2;

        //condition to ensure the enemy will move
        if (x == 0){
            UorD = 1;
        } else if (x == 4){
            UorD = 0;
        }

        if (UorD == 0 && validMove((x-1), y)){
            //only moves if the enemy will hit the player, or move to an empty space
            //prevents enemies from affecting chests, or each other
            if (startEvent(b, (x-1), y, thisEntity) || b[x-1][y] == '-'){
                x -= 1;
                moved = true;
            }
        } else if (UorD == 1 && validMove((x+1), y)){
            if (startEvent(b, (x+1), y, thisEntity) || b[x+1][y] == '-'){
                x += 1;
                moved = true;
            }
        }
    } else {
        //50/50 chance to move left or right
        srand(time(0));
        int LorR = rand() % 2;

        if (y == 0){
            LorR = 1;
        } else if (y == 4){
            LorR = 0;
        }

        if (LorR == 0 && validMove(x, (y-1))){
            if (startEvent(b, x, (y-1), thisEntity) || b[x][y-1] == '-'){
                y -= 1;
                moved = true;
            }
        } else if (LorR == 1 && validMove(x, (y+1))){
            if (startEvent(b, x, (y+1), thisEntity) || b[x][y+1] == '-'){
                y += 1;
                moved = true;
            }
        }
    }
    
    //checks if the entity moves
    if (!moved){
        return false;
    } else {
        b[ogX][ogY] = '-';
        //only changes bossPos if a boss is being moved
        if (boss){
            bp[0] = x;
            bp[1] = y;
        }
        //checks if a battle is triggered
        if (b[x][y] == player){
            return true;
        } else {
            b[x][y] = thisEntity;
            return false;
        }
    }
}

string acceptPlayerInput(char b[5][5], int pX, int pY){
    //get the player's desired move
    char playerChoice;
    cout << "Move where? (W/A/S/D to move, P to pause, I to use item, O to buy from the shop): ";
    cin >> playerChoice;
    playerChoice = toupper(playerChoice);

    bool moveDone = false;
    //changes player coordinates in accordance w/ their choice
    while (!moveDone){
        switch (playerChoice){
            case 'W':
                if (validMove((pX-1), pY)){
                    pX -= 1;
                    moveDone = true;
                } else {
                    cout << "Invalid move (out of bounds)" << endl;
                    //ensures the next run through the switch case will go to default
                    playerChoice = 'p';
                }
                break;
            case 'A':
                if (validMove(pX, (pY-1))){
                    pY -= 1;
                    moveDone = true;
                } else {
                    cout << "Invalid move (out of bounds)" << endl;
                    playerChoice = 'p';
                }
                break;
            case 'S':
                if (validMove((pX+1), pY)){
                    pX += 1;
                    moveDone = true;
                } else {
                    cout << "Invalid move (out of bounds)" << endl;
                    playerChoice = 'p';
                }
                break;
            case 'D':
                if (validMove(pX, (pY+1))){
                    pY += 1;
                    moveDone = true;
                } else {
                    cout << "Invalid move (out of bounds)" << endl;
                    playerChoice = 'p';
                }
                break;
            case 'P':
                return "Pause";
            case 'I':
                return "Item";
            case 'O':
                return "Shop";
            default:
                //handles improper inputs
                cout << "Invalid choice, please enter (W/A/S/D to move, P to pause, I to use item, O to buy from the shop): ";
                cin >> playerChoice;
                playerChoice = toupper(playerChoice);
        }
    }

    string newCoords = to_string(pX) + to_string(pY);
    return newCoords;
}

//pX and pY store where the player is
char changeBoard(char (&b)[5][5], int moves, int (&bp)[2]){
    //the boss moves once every 3 turns
    if (moves%5 == 0){
        bool cond = enemyMove(b, bp[0], bp[1], true, bp);
        if (cond){
            return 'b';
        }
    }

    if (moves%3 == 0){
        //only one random enemy can move at a time
        //enemyPos stores all the enemies' coordinates on the board to choose at random
        //max size is 23 because the max amount of available space on the grid at any given time is 23 (1 is always player, 1 is always boss)
        int enemyPos[23][2];
        int index = 0;

        for (int i = 0; i < 5; i++){
            for (int j  = 0; j < 5; j++){
                if (b[i][j] == enemy){
                    enemyPos[index][0] = i;
                    enemyPos[index][1] = j;
                    index++;
                }
            }
        }

        srand(time(0));
        if (index > 0){
            int r = rand() % index;
            bool cond = enemyMove(b, enemyPos[r][0], enemyPos[r][1], false, bp);
            if (cond){
                return 'e';
            }
        }
    }

    //code to spawn enemies/chests
    //enemies take priority over chests
    bool spawned = spawnEnemies(b);
    if (!spawned){
        spawnChest(b);
    }

    return 'n';
}