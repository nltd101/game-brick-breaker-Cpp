#include "pch.h"
#include "GenerateMapBaseLevel.h"
GenerateMapBaseLevel::GenerateMapBaseLevel()
{
}
void GenerateMapBaseLevel::setMapLevel(int temp[9][10], int level)
{
	int a[7][10][9] =
	{ {{0,1,0,0,1,0,1,1,0},
		{1,0,1,1,0,1,1,0,1},
		{1,0,1,1,0,1,1,0,1},
		{1,0,1,1,0,1,1,0,1},
		{1,0,1,1,0,1,1,1,0},
		{1,0,1,1,0,1,1,0,0},
		{1,0,1,1,0,1,1,0,0},
		{1,0,1,1,0,1,1,0,0},
		{1,0,1,1,0,1,1,0,0},
		{0,1,0,0,1,0,1,0,0}
		} ,

	   {{1,1,1,1,1,1,1,1,1},
		{0,1,1,1,1,1,1,1,0},
		{0,0,1,1,1,1,1,0,0},
		{0,0,0,1,1,1,0,0,0},
		{0,0,0,0,1,0,0,0,0},
		{0,0,0,1,1,1,0,0,0},
		{0,0,1,1,1,1,1,0,0},
		{0,1,1,1,1,1,1,1,0},
		{1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0}},

	   {{0,0,0,0,0,0,0,0,0},
		{0,1,1,1,0,1,1,1,0},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{0,1,1,1,0,1,1,1,0},
		{0,0,1,1,0,1,1,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0}},

	};
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			temp[i][j] = a[level][j][i];
		}
	}
	GenerateItem(temp);
}
void GenerateMapBaseLevel::GenerateItem(int a[9][10])
{
	for (int i = 0; i < 10; i++)
	{
		int icoin = rand()%9;
		int jcoin = rand() % 10;
		if (a[icoin][jcoin]!=0)
		{
			a[icoin][jcoin] = 4;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		int icoin = rand() % 9;
		int jcoin = rand() % 10;
		if (a[icoin][jcoin] != 0)
		{
			a[icoin][jcoin] = 3;
		}
	}
	int countheart = 3;
	while (countheart!=0)
	{
		int icoin = rand() % 9;
		int jcoin = rand() % 10;
		if (a[icoin][jcoin] != 0)
		{
			a[icoin][jcoin] = 2;
			countheart--;
		}
	}
};
