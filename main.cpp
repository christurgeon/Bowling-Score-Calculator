// File: main.cpp
// Need to pass "-std=c++11" to compiler in order to access 'std::to_string' function 

#include "Bowling.h"
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
using namespace std;


void writeOut(const vector<string>& output, char* fileOut) {
    /* This function outputs each line for the scoreboard, which is located 
    within a vector, into the output file stream by means of a while loop. */
	ofstream out_str(fileOut);
    // Checking to make sure file was opened successfully
	if (!out_str.good()) {
   		cerr << "Failed to open " << fileOut << " to write." << endl;
    	exit(1);
	}
    unsigned int o = 0;
    while (o < output.size()) {
        out_str << output[o] << endl;
        ++o;
    }
    out_str.close();
} 


int main(int argc, char* argv[]) {
	// Vector which holds player objects
	vector<Bowling> game_tracker; 
	// Opening file to read
	ifstream in_str(argv[1]);
    if (!in_str.good()) { 
    	cerr << "Failed to open " << argv[1] << ".txt to read." << endl;
    	exit(1);
    } // If not enough arguments are given.
    if (argc < 4) {
        cerr << "Missing argument(s). Please try again." << endl;
    }

    // Extracting player's name and integer scores from string using stringstream
    // Name and scores are used to create object which is added to vector
    string in, first, last;
    int width = 0;
    vector<string> nine_frames, final_frame, complete_game, input;
    vector<int> scores_list;

    // Reading in scores and names
    while (in_str >> in) { 
        input.push_back(in); }

    unsigned int j = 0;
    while (j < input.size()-1) {
        // Extracts the name
        if ( isalpha(input[j][0]) && isalpha(input[j+1][0]) ) {
            first = input[j];
            last = input[j+1];
            int name_length = first.length() + 1 + last.length();
            // Finds longest name
            if (name_length > width) { width = name_length; }
            j += 2;
            continue;
        }
        else { // Converts string to integer and adds integer to vector
            while (!isalpha(input[j][0]) && j < input.size()-1) {
                int y = atoi(input[j].c_str());
                scores_list.push_back(y);
                ++j;   
            } // Creates class objects
            if (j == input.size() - 1) { // Final integer in input
                int y = atoi(input[j].c_str());
                scores_list.push_back(y); 
            }
            game_tracker.push_back( Bowling(first, last, scores_list) );
            // Checking the input file
            if (scores_list.size() < 11 || scores_list.size() > 21) { 
                cerr << "Invalid number of scores within input file..." << endl;
                exit(1);
            }
            scores_list.clear();

        }
    }       

    // Sorts class objects by last name
    sort(game_tracker.begin(), game_tracker.end(), lessThan);  
    // Creates horizontal border of dashes
    complete_game.push_back( string(width+66, '-') );
    for (unsigned int i=0; i < game_tracker.size(); ++i) {
        nine_frames = game_tracker[i].nineFrames();
        final_frame = game_tracker[i].finalFrame(); 
        // pringGame formats the each player's game into two lines
        vector<string> gm = printGame(nine_frames, final_frame, width, game_tracker[i].getFirstName(), game_tracker[i].getLastName()); 
        complete_game.push_back(gm[0]); 
        complete_game.push_back(gm[1]);
        complete_game.push_back( string(width+66, '-') );
    }

    string arg = argv[3];
    // Implements unique statistic
    if (arg == "custom") {
        // Finds spacing between name and score
        int score_length;
        complete_game.push_back(""); // Empty line
        for (unsigned int i=0; i < game_tracker.size(); ++i) {
            vector<int> stk = game_tracker[i].longestStreak();
            // Get largest streak by sorting vector and getting last value
            sort(stk.begin(), stk.end());
            int highest = stk.back();
            score_length = to_string(highest).length();
            string line = game_tracker[i].getFirstName() + ' ' + game_tracker[i].getLastName();
            string spaces = string( ((width + 5) - line.length() - score_length), ' ' );
            line += spaces + to_string(highest);
            complete_game.push_back(line);
        }
        writeOut(complete_game, argv[2]); 
    } 
    // Standard game 
    else if (arg == "standard") {
        complete_game.push_back("");
        string line;
        int score_length; 
        // Sorts by score
        sort(game_tracker.begin(), game_tracker.end(), lessThanScore);
        // Finds spaces between name and score for formatting purposes
        for (unsigned int i=0; i < game_tracker.size(); ++i) {
            line = game_tracker[i].getFirstName() + ' ' + game_tracker[i].getLastName();
            score_length = to_string(game_tracker[i].getScore()).length();
            string spaces = string( ((width + 5) - line.length() - score_length), ' ' );
            line += spaces + to_string(game_tracker[i].getScore());
            complete_game.push_back(line); 
        }     
        writeOut(complete_game, argv[2]);   
    }
    else { // If standard or custom are not entered
        cerr << "Invalid command entered, please try again." << endl;
        exit(1);
    }
	return 0;
}