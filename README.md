# Bowling-Score-Calculator
This C++ program reads in bowling players' names and their scores for a game from a text file and it calculates and formats the game into a bowling score sheet, which is then written to a text file. It consists of a Bowling class and a main.cpp file. 

## Command Line Arguments
* ```./a.out INPUT_FILE OUTPUT_FILE GAME_STATS```
* Compile with ```-std=c++11``` to use ```st::to_string``` function

## Clarification
1. ```INPUT_FILE```: the file that the game data is read from.
2. ```OUTPUT_FILE```: the file that the result data is written to.
3. ```GAME_STATS```: can either pass ```standard``` or ```custom``` to see a stat that shows the longest streak.
