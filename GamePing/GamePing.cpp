// GamePing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#include "pch.h"
#include <iostream>
#include "game.h"
#include <conio.h>
#include "TopHighScore.h"
#define _WIN32_WINNT 0x0500
#include <windows.h> 
int main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	Game game;
	game.run();
	return EXIT_SUCCESS;
}