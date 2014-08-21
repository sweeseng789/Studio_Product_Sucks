#include "mainmenu.h"
#include "game.h"

#include <iostream>
#include <iomanip>

void MainMenu()
{
	string Menu[4] = {"PLAY", "HIGHSCORE", "CONTROLS", "EXIT"}; // Variables in the Menu
	int pointer = 0;

	while(true)
	{
		system("cls");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		std::cout << "WELCOME TO BATTLEZONE" << std::endl;		// Menu header
		std::cout << std::endl;

		for (int i = 0; i < 4; ++i)
		{
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				std::cout << Menu[i] << std::endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				std::cout << Menu[i] << std::endl;
			}
		}

		while(true)
		{
			if (GetAsyncKeyState(VK_UP) != 0)					// Up key input
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 3;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)			// Down key input
			{
				pointer += 1;
				if (pointer == 4)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch (pointer)
				{
				case 0:
					{
						mainLoop();								// Brings player into game
					} break;
				case 1:
					{
						std::cout << "High scores";				// Brings player to highscore screen
					} break;
				case 2:
					{
						Controls();								// Brings player to control screen
					} break;
				case 3:
					{
						exit(0);
					}break;
				}
			}
		}
		Sleep(150);
	}
}

void Controls()
{
	Sleep(150);
	system("cls");
	std::cout << "CONTROLS" << std::endl;
	std::cout << std::endl;
	std::cout << "LEFT  : LEFT ARROW KEY" << std::endl;
	std::cout << "RIGHT : RIGHT ARROW KEY" << std::endl;
	std::cout << "SHOOT : Spacebar" << std::endl;
	std::cout << "PAUSE : P" << std::endl;
	std::cout << "SELECT: ENTER" << std::endl;

}

void Pause() 
{
	if (GetAsyncKeyState('P') || GetAsyncKeyState('p') != 0)
	{
		system("PAUSE");
	}
}

void Back()				//Back function
{
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "BACK" << std::endl;		

}