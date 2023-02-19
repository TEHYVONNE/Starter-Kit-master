# Part 2

## Video Demo

[Video Demo](https://youtu.be/BSM0Xb7QNX0).

## Minimum Requirements

### Completed

List all the features completed.

1. Game Board (including Alien, randomised zombies and objects)
2. Default Game settings and customisation (board rows, board columns, zombie count)
3. Game Characters (alien's attack will start from zero at each turn, life at 100 at the beginning of the game)
4. Alien move (Alien will stop when it hit the border/rock/attack zombie, when alien find a pod it will attack one zombie)
5. Trails reset with random objects
6. Zombie move (move one step in a randomly selected direction which is not occupied by Alien, attack alien if alien is within its attack range)
7. Multiple zombies (each zombies will have different life, attack and range which are generated randomly)
8. Game objects (arrow, health, pod, rock, empty, trail)
9. Game controls (up, down, left, right, arrow, save, load, quit)

### To Do

List all the features not yet done. Remove this section if there is no incomplete requirements.

1. Arrow pointing character's turn.

## Additional Features

1. @ - It is hide under the rock. When alien find it, alien's attack will x2.

## Contributions

List down the contribution of each group members.

### Tan Hui Jeen

1. Randomly generate game board.
2. Game controls (quit, save, load, up, down, left, right, arrow).
3. Title.
4. Alien and Zombie (life, attack, range)
5. class Alien
6. moves: pod to attack zombie
7. Zombie movements (attack alien/trails)
8. Changing arrows directions
9. Alien movements (when hit rock/attack zombie/trails)

### Teh Yvonne

1. Default game settings and customisation.
2. Randomly generate game board.
3. Game controls (help, save, load, up, down, left, right, arrow).
4. Alien and Zombie (life, attack, range)
5. class Zombie
6. moves (health/arrow/empty/trail)
7. Changing arrows directions
8. Zombie movements (attack alien)

## Problems Encountered & Solutions

Describe the problems encountered and provide the solutions / plan for the solutions.
1. Inconsistent, might have bugs sometimes, or it might run smoothly.
plan sol: still not sure.

2. Allow player to play smoothly when loaded.
plan sol: Save alien position.

3. Zombies attack alien in the wrong range sometimes.
plan sol: initialise zombie index so that it knows the range.

4. Zombies will not lose (negative numbers sometimes).
plan sol: modifying the if statement.