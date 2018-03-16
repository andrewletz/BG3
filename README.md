# ![Icon](https://i.imgur.com/chHWOCG.png) BG3

A game based on Starcraft II's "**g**ood **g**reat **b**est **g**ame". Built with C++ and SFML (and a little bit of make).

![Screencaps](https://i.imgur.com/MlKT3C3.png)

## Description

BG3 is a simple video game based on the arcade mode from Starcraft 2 titled “good great best game”. The game field is split into two sides, left and right, both with a home base that can defend itself from attackers. Each player is given a random selection of distinct units at the start of each match with different strengths and costs (not implemented yet). The game is split into rounds where each player has a short amount of time to place units on their side of the field in whatever arrangement seems best. Once a round begins, the units walk towards each other and fight wherever they meet, the winning side pushing towards the enemies base. Depending on the time taken for the round, each player receives an equal amount of income. Once one side’s base is destroyed, they lose.

The difficulty factor comes from the short time allotted each round to place units, where each player must decide which arrangement will be best to counter their opponent’s army. The composition of units will decide which attacks first, meaning it is important where they are placed. For example, if the ranged units are placed in front of the melee units, it will cause pathing issues as the melee units are unable to fight from behind.

## Compilation

Go into the Game folder and type make. If all goes well, you should be able to run BG3.exe.

## Status

The game is playable, but is not complete with all the features one might expect out of a fully-fledged game.
Sadly it is not compatible with Windows yet as it wasn't a huge priority.

## Dependencies

You must have a compatible version of SFML installed on your machine, along with make to compile the binaries.

## Team Members

* Andrew Letz
  * Makefile
  * Round/game logic
  * Team logic
  * Dynamic resolution scaling
  * Art assets
* Ethan Quick
  * Buttons/Containers
  * Timers
  * Other UI elements
  * Pause state
* Tristan Colby
  * Unit class design
  * Collision detection
  * Unit combat/movement logic
  * Unit integration with rounds/team
  
## Credits

Thank you to Daniel Mansfield for your SFML intro tutorial located here: https://github.com/dbMansfield/citybuilder
