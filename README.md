# ENGG1340 Group Project

## Group No.: 141

## Team Members:
Sutikno Alicia (3035946136)

Hardiwijaya Theodore Bryan (3035946734)

## Chosen text-based game:
Ancient Loop (Self-made RPG game)

## Description of the game:
Ancient Loop is a classic role-playing game, where the player goes on an adventure to defeat the 3 bosses and protect the kingdom from danger. In Ancient Loop, the player will go into battle with different enemies, such as slimes, goblins, evil horses, skeletons and mages, and be rewarded with gold. By earning gold, the player will be able to purchase items from the shop, which will help the player in defeating the bosses.

## Set-up:
- The player will play on a 5x5 board. 
- The game starts out with 1 boss and 1 enemy on the board. 
- The boss will always be positioned on the top center of the board, and the enemy’s position will be randomized in every run of the game.
- After the boss is defeated, a new board will be printed.

(1) Player Base Stats:
- HP: 25
- Attack: 20
- Defense: 15
- Gold: 0

(2) Enemy Base Stats:
- HP: 20
  - HP for every subsequent board will increase by 10
- Attack: 15
  - Attack for every subsequent board will increase by 10
- Defense: 8
  - Defense for every subsequent board will increase by 10
- Gold dropped: 10
  - Gold dropped for every subsequent board will increase by 10
 
(3) Boss Base Stats:
- HP: 40
  - HP for every subsequent boss will increase by 20
- Attack: 20
  - Attack for every subsequent boss will increase by 10
- Defense: 15
  - Defense for every subsequent boss will increase by 10
- Special Attack: 5
  - Special Attack for every subsequent boss will increase by 5
- Gold dropped: 100
  - Gold dropped for every subsequent boss will increase by 100

## Gameplay:
- The player will then be able to move Upwards (W), Leftwards (A), Downwards (S), and Rightwards (D).
- Every turn, chests will have a 10% chance of spawning, and enemies will have a 30% chance of spawning.
- Chests:
  - If the player opens a chest, the player will be able to receive gold or any of the 3 items, with varying stats.
- Shop:
  - There will be a shop, which has 4 standard items (never changes) and 1 special item, which will change every 5 turns. The player will be able to purchase items using gold, which is earned by opening chests or defeating enemies.
- Enemies & Bosses:
  - Enemies can spawn in any empty space on the board, but there can only be only 1 boss at a time.
  - Every 3 turns, one of the enemies on the board will be able to make a move. 
    - Valid move: The new position is empty or the new position of the enemy is the new position of the player.
    - If the enemy moves into a position occupied by a chest, another enemy or the boss, the move will be invalid, and the enemy will make no moves for that turn.
    - If the enemy moves into the new position of the player, the battle scene is commenced, and the enemy will make the first move.
  - Every 5 turns, the boss on the board will be able to make a move.
    - Valid move: The new position is empty or the new position of the boss is the new position of the player.
    - If the boss moves into a position occupied by a chest or an enemy, the move will be invalid, and the boss will make no moves for that turn.
    - If the boss moves into the new position of the player, the battle scene is commenced, and the boss will make the first move.
- If the player comes into contact with an enemy or a boss, the player will be able to make the first move.
- Upon defeat, bosses will drop gold, which may be used to purchase items from the shop.
- If the player dies during any battle, the game will end, and the player will have to restart from the beginning.
- If a boss is successfully defeated, a new board will be generated, and a more powerful boss will be on the board.
- After defeating a total of 3 bosses, the player wins the game, and the game ends.
- 
## Game Instructions/ Rules:
(1) Press W, A, S, or D to move up, left, down or right 


(2) The player can enter P or O to enter the Pause menu or Shop menu on every turn

(3) Move towards an enemy, boss or chest to interact with them

(4) For every game event, a prompt will be shown on the screen to help the player input correctly. Please follow the prompts.

## Game Assumptions:
- The player will always input data that is of the correct data type

## Implemented Game Features and the Coding Requirements:
### (1) Generation of random game sets or events
- Generation of enemies: Every time a new board is printed, there is a random chance of whether or not an enemy will appear in that board
  - The type of enemy which will appear is also random
- Shop items: For every 5 steps/moves the player makes, the random item in the shop will be a stronger version of any of the 3 item types. The 4 other items in the shop are constant.
- Chests in the overworld: The generation of a chest is random, and its contents are also randomized. A chest can contain gold or any of the 3 items: weapons, potions, armors and charms
- Critical hits done towards enemies and bosses

### (2) Data structures for storing game status
- Structures are used to store data about the player, enemies and the items
- Vector is used to represent the player’s inventory
- Arrays are used to store information about the map, boss names, enemy/boss symbols and position of the boss
- String is used as return value in function acceptplayerinput as a way to return 2 integers

### (3) Dynamic memory management
- We used vectors to represent the player’s inventory as there is no fixed amount of items that a player can store in their inventory. This will be limited by the amount of gold a player has.

### (4) File input/output (e.g., for loading/saving game status)
- There are text files (.txt) taken as input, which will output ASCII art
- There will be a save option for the player in the pause menu. If the player chooses to exit the game, the game will be saved automatically.
  - Inside the save file (save.txt): player stats, player inventory, and current playing board
- At the start menu, the player will be able to choose if they want to load an old game, or start a new game.
  - If the player tries to load a game, but there is no save file, a new game will start

### (5) Program codes in multiple files
- mainStruct.cpp & mainStruct.h: contains structures for the player, enemy and items, and a vector of items to represent the inventory
- battle.cpp & battle.h: program run during battle
- board.cpp & board.h: program used for board initialisation, board printing, checking for valid moves, starting an event (battle/chest), chest & enemy spawning, determining enemy moves, accepting player input & changing the board every move
- menu.cpp & menu.h: contains start, pause, battle, inventory and end menus which will be displayed on the correct occasion
- shop.cpp & shop.h: displays the shop menu, and allows the player to purchase items; will also deduct the player’s funds and store the items in the player’s inventory upon purchase
- saveload.cpp & saveload.h: saving and loading mechanism of the game; allows the player to save their game and start again where they left off
- main.cpp: contains the driver code
- Makefile: creates object files (.o) and links them together to allow the game to be executed/played

## Compilation and Execution Instructions:
### Option 1:
Individual .h, .cpp files and the Makefile will be provided. Option 1 is if you want to compile, and create the object files on your own.
(1) Upload the project folder to the academy server
(2) Access the academy server
(3) Open the terminal in the project folder
(4) Run make AL
(5) Run ./AL
(6) The game will start

### Option 2:
Option 2 is if you want to run the game, with no compilation required. The .h and .cpp files, along with the .o files, will be provided in the project folder. 
(1) Upload the project folder to the academy server
(2) Access the academy server
(3) Open the terminal in the project folder
(4) Run ./AL
(5) The game will start

## Final Notes to the Player:
Since X2GO does not execute our program correctly sometimes, please restart the game and run the program in a new terminal tab if there is nothing being output on the screen. Thank you, and we hope you enjoy our game!

