// File: Bowling.h

#include <string>
#include <vector>
using namespace std;

class Bowling {
public:	
	// Constructors
	Bowling();
	Bowling(const string& first_name, const string& last_name, const vector<int>& scores_list); 

	// Accessors 
	int getScore();
	int getThrow();
	const string& getFirstName() const; 
	const string& getLastName() const;
	vector<int> longestStreak();

	// Modifiers
	void setScore(int Score); 
	void setThrow(int Throw);
	void hotStreak();
	void notHotStreak();

	// Create frames
	vector<string> nineFrames(); 
	vector<string> finalFrame(); 

private: // Member variables
	string first;
	string last;
	int running_score;
	int streak;
	int throw_number;
	vector<int> scores;
	vector<int> streak_tracker;
	vector<string> frame_output;
};

// Modify frame score for special condition strike/spare
int strike(const int throw_one, const int throw_two);
int spare(const int throw_one);	

// Return a vector containing two strings: one is the first 
// line of a player's game and the second is the second line.
vector<string> printGame(const vector<string>& first_nine, const vector<string>& tenth, const int width, const string first_name, const string last_name);

// Class object comparison functions
bool lessThan(Bowling const&a, Bowling const& b);
bool lessThanScore(Bowling &a, Bowling &b);