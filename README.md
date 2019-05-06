# Bowling-Score-Calculator
This C++ program reads in bowling players' names and their scores for a game from a text file and it calculates and formats the game into a bowling score sheet, which is then written to a text file. It consists of a Bowling class and a main.cpp file. 

## Command Line Arguments
* ```./a.out INPUT_FILE OUTPUT_FILE GAME_STATS```
* Compile with ```-std=c++11``` to use ```st::to_string``` function

## Clarification
1. ```INPUT_FILE```: the file that the game data is read from.
2. ```OUTPUT_FILE```: the file that the result data is written to.
3. ```GAME_STATS```: can either pass ```standard``` or ```custom``` to see a stat that shows the longest streak.

## Example
```
./a.out simple_tenth.txt out.txt standard
```
```
------------------------------------------------------------------------------
| George Adams | 2 / | - 3 | 2 / | - / | 1 / | 2 2 | 5 / | 6 / | 2 / | 1 1   |
|              |  10 |  13 |  23 |  34 |  46 |  50 |  66 |  78 |  89 |    91 |
------------------------------------------------------------------------------
| Sally Smith  |   X | 2 3 |   X |   X | 5 1 |   X | - - | 9 / |   X | 2 2   |
|              |  15 |  20 |  45 |  61 |  67 |  77 |  77 |  97 | 111 |   115 |
------------------------------------------------------------------------------

Sally Smith   115
George Adams   91
```
