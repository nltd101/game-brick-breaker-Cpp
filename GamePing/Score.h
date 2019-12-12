#pragma once
#include <iostream>
#include <sstream>
#include "SFML/Network.hpp"
#include "string"
using namespace std;
class Score
{
private:
	string name;
	string score;
public:
	string get_name();
	string get_score();
	Score(string, string);
	Score();
	string pushScore();
};

