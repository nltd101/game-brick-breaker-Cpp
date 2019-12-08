#pragma once
#include "SFML/Network.hpp"
#include <iostream>
#include "Score.h"
#include "vector"
using namespace std;
class TopHighScore
{
public:
	vector<Score*> getHighScore();
};

