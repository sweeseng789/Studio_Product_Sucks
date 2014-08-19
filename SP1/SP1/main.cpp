#include <iostream>
#include <windows.h> //For cls

using std::cin;
using std::cout;
using std::endl;

char map [20] [20] = {
	"*******************",
	"*                 *",
	"*   V V V V V V   *",
	"*    V V V V V    *",
	"*     V V V V     *",
	"*      V V V      *",
	"*       V V       *",
	"*        V        *",
	"*                 *",
	"*                 *",
	"*                 *",
	"*                 *",
	"*                 *",
	"*                 *",
	"*                 *",
	"*                 *",
	"*                 *",
	"*                 *",
	"*        A        *",
	"*******************"
	};

bool endgame = false; //End game condition
int gamespeed = 50; //Adjust speed of game

int main()
{
	system("color 0a"); //For colour

	while (endgame == false) { //cout the map
		system("cls"); //to cout only one map instead of infinite
		for (int a = 0; a < 20; a++)
		{
			cout << map[a] << endl;
		}//cout map code ends here

		for (int a = 0; a < 20; a++)
		{
			for (int b = 0; b < 20; b++)
			{
				switch (map[a] [b])
				{
				case 'A': if (GetAsyncKeyState(VK_LEFT) != 0) //Code to move left
						  {
							  int b2 = b-1;
							  switch (map[a] [b2])
							  {
							  case ' ':
								  map[a] [b] = ' ';
								  b--;
								  map[a] [b2] = 'A';
								  break;
							  }
						  } //Code to move left ends here

						  if (GetAsyncKeyState(VK_RIGHT) != 0) // Code to move right
						  {
							  int b2 = b+1;
							  switch (map[a] [b2])
							  {
							  case ' ':
								  map[a] [b] = ' ';
								  b++;
								  map [a] [b2] = 'A';
								  break;
							  }
						  } //Code to move right end here

						  if (GetAsyncKeyState(VK_SPACE) != 0)
						  {
							  a--;
							  map[a] [b] = '^'; //Code for shooting only 1 player bullet
						  }
						  break;

				case '^': //Code for shooting player bullet
					map[a] [b] = ' ';
					a--;

					if (map[a] [b] != '*' && map[a] [b] != 'V')
					{
						map[a] [b] = '^';
					}
					else if (map[a] [b] == 'V')
					{
						map[a] [b] == ' ';
					}
					break;//Code for player bullet end here
				}
			}
		}
		Sleep(gamespeed); //Adjust speed of game
	}
}