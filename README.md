# Mini Rouge Dungeon
# Demos of this game
Click on the link to download and see the demo of this game.
[Link](game)
You can also compile the game by cloning this repo and run:

'''sh
g++ -o game *.cpp
./game
'''

# Introduction
This is a rouge-like game I designed using C++ with an object-oriented design. In this game, the player has to fight through four levels, beat the monsters, and pick up the trophy at level 4 to win the game.

# Difficulties and Achievements
There are two main difficulties I encoutered in this game.
1. Room generation:
Since the rooms have to be a square shape generated in a specific area, I have to specify psedurandom areas for generating theses
squares. Each room also needs to have a route(routes) connecting to each other, so I chose random points on the rooms' edges to 
form the room allays.

2. Goblin Algorithm:
(P.s. At the time I designed this game, I haven't learnt bfs.)
Since goblin in this game is a smart creature (it always finds the shortest paths to the player), I used an optimized dfs for their path findings. Dfs is not the best approach, especially the map has multiple goblins. But, if I took a note of the visited
grid, marking it with distance number (instead of visited status), avoiding the possible cycles and not necessary repetitive steps. As a result, this game could run smoothly even with dfs.  

Achievement:
From this game, I learned how to maintain a good object-oriented design. Some pathfinding algorithms also blown my mind, and by comparing the efficiency of using different algorithms, I saw the glamour of picking up the best algorithms to solve the problem.

# Game Symbols:
'#': Wall
' ': Empty space
'@': Player
'S': Snakewoman
'G': Goblin
'D': Dragon
'B': Bogeyman
'?': Scroll
')': Weapon

# How to play
1. **Move**: 'hjkl' or arrow keys 
2. **Fight**: Walk towards the node with the monster, and you'll see the prompt
3. **Grab**: Press 'g' to pick up item on the ground
4. **Inspect**: Press 'i' to see your inventory
5. **Cheat**: Press 'c' to enter the cheat mode
6. **Wield**: Press 'w' to go to the inventory, and press the corresponding weapon number to wield weapons
7. **Read**: Press 'r' to go to the inventory, and press the corresponding scroll number to read scroll
8. **Next Floor**: Stand on the '>' and press 'shift' and '>' to go to the next floor 

The following are the design docs, and you could see how I implement this program by reading through it. It took like 10 minutes to
read.
[Link](report.txt)

Contents:
  2.1 Dungeon
  2.2 Actor
    2.2.1 Monsters
    2.2.1.n Each Monster (int n; n <= 4 && n>=1)
  2.2.2 Player
  2.3 Items
    2.3.1 Weapons
    2.3.2 Scrolls
  2.4 Menu
  2.5 Game

