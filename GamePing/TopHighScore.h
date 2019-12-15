#pragma once
#include "SFML/Network.hpp"
#include <iostream>
#include "Score.h"
#include <vector>
#include <fstream>
using namespace std;
class TopHighScore
{
private:
	bool checkTrash(char x);
	
public:
	vector<Score*> getHighScore();
	vector<Score*> convertFromString(string S);
};

