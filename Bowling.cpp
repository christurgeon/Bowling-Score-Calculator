// File: Bowling.cpp

#include <iostream> 
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include "Bowling.h"
using namespace std;

// Default constructor
Bowling::Bowling() {
	first = "Unknown";
	last = "Unknown";
	running_score = 0;
	streak = 0;
	throw_number = 0;
	vector<int> scores_list;
	scores = scores_list; // Empty vector
}

// Construct from player's name and all scores
Bowling::Bowling(const string& first_name, const string& last_name, const vector<int>& scores_list) {
	first = first_name;
	last = last_name;
	running_score = 0;
	streak = 0;
	throw_number = 0;
	scores = scores_list;
}

// Used to access total score
int Bowling::getScore() { 
	return running_score;
}

// Funtion updates the total score
void Bowling::setScore(int Score) {
	running_score += Score;
}

// Used to access first name
const string& Bowling::getFirstName() const {
	return first; 
}

// Used to access last name
const string& Bowling::getLastName() const { 
	return last; 
}

// Returns the number of throws made
int Bowling::getThrow() {
	return throw_number;
}

// Increments the number of throws
void Bowling::setThrow(int Throw) {
	throw_number += Throw;
}

// Keeps track of the number of consecutive strikes or spares made
void Bowling::hotStreak() {
	++streak;
}

// When spare/strike streak is ended, the streak number is added to a vector and then the value is reset
void Bowling::notHotStreak() {
	streak_tracker.push_back(streak);
	streak = 0;
}

// Returns the vector containing the streaks
vector<int> Bowling::longestStreak() {
	return streak_tracker;
}

// Updates the running score for strike condition
int strike(const int throw_one, const int throw_two) {
	int strike_score = (10 + throw_one + throw_two);
	return strike_score;
}

// Updares the running score for spare condition
int spare(const int one_throw) {
	int spare_score = (10 + one_throw);
	return spare_score;
}

// Formats the final frame
vector<string> Bowling::finalFrame() {
	vector<string> final;
	int idx = getThrow(); // Gives starting index of scores for final frame 
	string line_one, line_two, final_throw, total_score; 

	if (scores[idx] == 10) { // IF STRIKE IS FIRST
		int frame_score = strike(scores[idx+1], scores[idx+2]);
		setScore(frame_score);
		hotStreak();
		line_one = "X";
		// Formats topline of frame for all combinations of throws
		if (scores[idx+1] == 10) { line_one += " X";  hotStreak(); 
			if (scores[idx+2] == 0) { line_one += " -"; }
			if (scores[idx+2] == 10) { line_one += " X"; hotStreak(); }
			else { line_one += ' ' + to_string(scores[idx+2]); }
		}
		else if (scores[idx+1] + scores[idx+2] == 10) { 
			hotStreak();
			if (scores[idx+1] == 0) { line_one += " - /"; }
			else {line_one += ' ' + to_string(scores[idx+1]) + " /"; }
		}	
		else {
			if (scores[idx+1] == 0) { line_one += " -"; }
			else { line_one += ' ' + to_string(scores[idx+1]); }
			if (scores[idx+2] == 0) { line_one += " -"; }
			else { line_one += ' ' + to_string(scores[idx+2]); }
		}
		line_one += " |";
	}
	else if (scores[idx] + scores[idx+1] == 10) { // IF SPARE IS FIRST
		int frame_score = spare(scores[idx+2]); 
		setScore(frame_score);
		// Formats first line for three throws
		if (scores[idx+2] == 10) { final_throw = " X";  hotStreak(); }
		else if (scores[idx+2] == 0) { final_throw = " -"; }
		else { final_throw = ' ' + to_string(scores[idx+2]); } 
		(scores[idx] == 0) ? (line_one = "- /") : (line_one = to_string(scores[idx]) + " /");
		line_one += final_throw + " |";
	}
	else { // IF TWO THROWS ONLY
		int frame_score = scores[idx] + scores[idx+1];
		setScore(frame_score);
		(scores[idx] == 0) ? (line_one = "- ") : (line_one = to_string(scores[idx]) + ' ');
		(scores[idx+1] == 0) ? (line_one += "-  ") : (line_one += to_string(scores[idx+1]) + "  ");
		line_one += " |";
	}
	// Updates total score, creates lower line of frame and adds strings to vector
	total_score = to_string(getScore());
	line_two = string(5 - total_score.length(), ' ') + total_score + " |";
	final.push_back(line_one);
	final.push_back(line_two);
	return final;
}

vector<string> Bowling::nineFrames() {
	/* This function takes in a vector containing the scores as integers. 
	It configures the first 9 rounds and outputs each round's scores and 
	running score as strings. */
	vector<string> frame_output;
	unsigned int i = 0, frame_cnt = 1, num_size; 
	string line_one, line_two, ln1, ln2;
	while (i < scores.size() && frame_cnt < 10) { // Ensures only first 9 frames are made
		int throw_one = scores[i];
		int throw_two = scores[i+1];
		bool activate_if = true;
		if (throw_one == 10 && activate_if) { // STRIKE CONDITION
			int frame_score = strike(scores[i+1], scores[i+2]); 
			setScore(frame_score);  
			int total_score = getScore();
			line_one = "  X"; 
			// This line ensures a right justification and proper spacing
		    num_size = to_string(total_score).length();
			line_two = string(3 - num_size, ' ') + to_string(total_score);
			activate_if = false;
			hotStreak();
			setThrow(1);
			i += 1;
		} 
		if ((throw_one + throw_two) == 10 && activate_if) { // SPARE CONDITION
			int frame_score = spare(scores[i+2]); 
			setScore(frame_score);
			int total_score = getScore(); 
			// Dealing with formatting for spare symbol and if first throw is 0
			if (throw_one == 0) { line_one = "- /"; }
			else { line_one = to_string(throw_one) + " /"; }
			num_size = to_string(total_score).length();
			line_two = string(3 - num_size, ' ') + to_string(total_score);
			activate_if = false;
			hotStreak();
			setThrow(2);
			i += 2;
		}
		if ((throw_one + throw_two) < 10 && activate_if) { // LESS THAN 10 PINS 
			setScore(throw_one + throw_two);	
			int total_score = getScore();
			string t1, t2;
			(throw_one == 0) ? (t1 = "-") : (t1 = to_string(throw_one) );
			(throw_two == 0) ? (t2 = "-") : (t2 = to_string(throw_two) ); 
			line_one = t1 + ' ' + t2; 
			num_size = to_string(total_score).length();
			line_two = string(3 - num_size, ' ') + to_string(total_score);
			notHotStreak();
			setThrow(2);
			i += 2;
		}
		ln1 += line_one + " | ";
		ln2 += line_two + " | ";
		++frame_cnt;
	}
	frame_output.push_back(ln1);
	frame_output.push_back(ln2);
	return frame_output; 
}

vector<string> printGame(const vector<string>& first_nine, const vector<string>& tenth, const int width, const string first_name, const string last_name) {
	/* Formats two lines, the first containing player name and number of pins knocked down per throw
	 and the second line outputs the running score that is updated in each frame. */
	vector<string> complete_game;
	string fst, lst, line_one, line_two;
	fst = first_name;
	lst = last_name;
	int name_length = fst.length() + lst.length() + 1;
	line_one = "| " + fst + ' ' + lst + string(width-name_length, ' ') + " | "; 
	line_two = "| " + string(width, ' ') + " | ";
	for (unsigned int i = 0; i < first_nine.size(); i += 2) {
		line_one += first_nine[i] + tenth[0];
		line_two += first_nine[i+1] + tenth[1];
	}
	complete_game.push_back(line_one); // First line tracking throws
	complete_game.push_back(line_two); // Second line tracking running score
	return complete_game;
}

// Formats player objects into alphabetical order
bool lessThan(Bowling const& a, Bowling const& b) {
	if (a.getLastName() < b.getLastName()) {
		return true; }
	if (a.getLastName() == b.getLastName() && a.getFirstName() < b.getFirstName()) {
		return true; }
	return false;
}

// Compares two bowlers by total score
bool lessThanScore(Bowling &a, Bowling &b) { // Can't be const
	if (a.getScore() > b.getScore()) {
		return true; }
	else { return false; }
}