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
	Score(string, string);
	string pushScore();
};

