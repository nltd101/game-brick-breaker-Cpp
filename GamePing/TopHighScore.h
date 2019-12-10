#pragma once
#include "SFML/Network.hpp"
#include <iostream>
#include "Score.h"
#include <vector>
#include <fstream>
using namespace std;
class TopHighScore
{
public:
	vector<Score*> getHighScore();
};

