#pragma once
#include <iostream>
using namespace std;
class GenerateMapBaseLevel
{
public:
	GenerateMapBaseLevel();
	int setMapLevel(int temp[9][10], int level);
private:
	void GenerateItem(int a[9][10]);
};

