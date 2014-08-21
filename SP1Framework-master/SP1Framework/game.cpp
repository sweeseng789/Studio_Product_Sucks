// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD consoleSize;
COORD left;
COORD right;
COORD up;
COORD down;
enemy unit[11];//maximum of 7 units of enemy type

void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.
    charLocation.X = consoleSize.X / 2;
    charLocation.Y = consoleSize.Y / 2;

    elapsedTime = 0.0;
}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	keyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
}

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the character based on the key press
    if (keyPressed[K_UP] && charLocation.Y > 0)
    {
        charLocation.Y-=2; 
    }
    if (keyPressed[K_LEFT] && charLocation.X > 0)
    {
        charLocation.X-=2; 
    }
    if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
        charLocation.Y+=2; 
    }
    if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 1)
    {
        charLocation.X+=2; 
    }

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;    
}

void render()
{
    // clear previous screen
    colour(0x0F);
    cls();

    //render the game

    //render test screen code (not efficient at all)
    const WORD colors[] =   {
	                        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	                        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	                        };
	
	for (int i = 0; i < 7; ++i)
	{
		gotoXY(i*12, 4);
		colour(colors[5]);
		std::cout << "Hit";
	}


    // render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

    // render character

	gotoXY(charLocation);
    colour(0x0C);

	user player ;//Player direction
	player.front = (char)192;
	player.back = (char)191;
	player.left = (char)170;
	player.right = (char)169;
	player.body =(char)233;

    gotoXY(charLocation);
    colour(0x0C);
	std::cout << player.body;
	if (GetAsyncKeyState(VK_UP) != 0)
	{
		std::cout << player.front;
	}
	else if (GetAsyncKeyState(VK_DOWN) != 0)
	{
		down.X = charLocation.X - 1;
		down.Y = charLocation.Y;
		gotoXY(down);
		std::cout << player.back;
	}
	else if (GetAsyncKeyState(VK_LEFT) != 0)
	{
		left.X = charLocation.X - 1;
		left.Y = charLocation.Y;
		gotoXY(left);
		std::cout << player.left;
	}
	else if (GetAsyncKeyState(VK_RIGHT) != 0)
	{
		right.X = charLocation.X + 1;
		right.Y = charLocation.Y;
		gotoXY(right);
		std::cout << player.right;
	}
	else if (GetAsyncKeyState(VK_UP) == 0)
	{
		std::cout << player.front;
	}

	//render enemy
	static int enemyCounter = 0;
	/** pattern for enemy spawning, 4, 3, 4... **/
	static double timePattern = 4;//starts at 4 sec

	// check if enemy unit is alive
	isEnemyAlive(timePattern);
	gotoXY(20, 0);
    colour(0x59);
    std::cout << timePattern << "patt" << std::endl;
	
	/** increase enemyPattern **/
	if(elapsedTime >= timePattern)
	{
		//cout each individual enemy unit
		if(unit[0].active == true)
		{
			static int X = consoleSize.X - 10;
			static int Y = 0;

			if(elapsedTime >= timePattern + 12)
			{
				X = consoleSize.X - 10;
				Y = 0;
			}

			if(Y < consoleSize.Y - 1)//not reach player line
			{
				enemyUnitAi(&X, &Y);//pass the incrementing of X and Y to ai function
			}

			gotoXY(X, Y);
			unit[0].location.X = X;//store X position for future collision detection
			unit[0].location.Y = Y;//store Y position for future collision detection
			std::cout << (char)233;
		}

		if(unit[1].active == true)
		{
			static int X = consoleSize.X / 2 - 10;
			static int Y = 0;

			if(elapsedTime >= timePattern + 12)
			{
				X = consoleSize.X /2 - 10;
				Y = 0;
			}

			if(Y < consoleSize.Y - 1)//not reach player line
			{
				enemyUnitAi(&X, &Y);//pass the incrementing of X and Y to ai function
			}

			gotoXY(X, Y);
			unit[1].location.X = X;//store X position for future collision detection
			unit[1].location.Y = Y;//store Y position for future collision detection
			std::cout << (char)233;
		}

		if(unit[2].active == true)
		{
			static int X = consoleSize.X / 2 + 10;
			static int Y = 0;

			if(elapsedTime >= timePattern + 12)
			{
				X = consoleSize.X /2 + 10;
				Y = 0;
			}

			if(Y < consoleSize.Y - 1)//not reach player line
			{
				enemyUnitAi(&X, &Y);//pass the incrementing of X and Y to ai function
			}

			gotoXY(X, Y);
			unit[2].location.X = X;//store X position for future collision detection
			unit[2].location.Y = Y;//store Y position for future collision detection
			std::cout << (char)233;
		}

		if(unit[3].active == true)
		{
			static int X = consoleSize.X - 70;
			static int Y = 0;

			if(elapsedTime >= timePattern + 12)
			{
				X = consoleSize.X - 70;
				Y = 0;
			}

			if(Y < consoleSize.Y - 1)//not reach player line
			{
				enemyUnitAi(&X, &Y);//pass the incrementing of X and Y to ai function
			}

			gotoXY(X, Y);
			unit[3].location.X = X;//store X position for future collision detection
			unit[3].location.Y = Y;//store Y position for future collision detection
			std::cout << (char)233;
		}
	}

	if(elapsedTime >= timePattern + 4)
	{
		//cout each individual enemy unit
		if(unit[4].active == true)
		{
			static int X = consoleSize.X - 20;
			static int Y = 0;

			if(elapsedTime >= timePattern + 12)
			{
				X = consoleSize.X - 20;
				Y = 0;
			}

			if(Y < consoleSize.Y - 1)//not reach player line
			{
				enemyUnitAi(&X, &Y);//pass the incrementing of X and Y to ai function
			}

			gotoXY(X, Y);
			unit[4].location.X = X;//store X position for future collision detection
			unit[4].location.Y = Y;//store Y position for future collision detection
			std::cout << (char)233;
		}

		if(unit[5].active == true)
		{
			static int X = consoleSize.X / 2;
			static int Y = 0;

			if(elapsedTime >= timePattern + 12)
			{
				X = consoleSize.X / 2;
				Y = 0;
			}

			if(Y < consoleSize.Y - 1)//not reach player line
			{
				enemyUnitAi(&X, &Y);//pass the incrementing of X and Y to ai function
			}

			gotoXY(X, Y);
			unit[5].location.X = X;//store X position for future collision detection
			unit[5].location.Y = Y;//store Y position for future collision detection
			std::cout << (char)233;
		}

		if(unit[6].active == true)
		{
			static int X = consoleSize.X - 60;
			static int Y = 0;

			if(elapsedTime >= timePattern + 12)
			{
				X = consoleSize.X - 60;
				Y = 0;
			}

			if(Y < consoleSize.Y - 1)//not reach player line
			{
				enemyUnitAi(&X, &Y);//pass the incrementing of X and Y to ai function
			}

			gotoXY(X, Y);
			unit[6].location.X = X;//store X position for future collision detection
			unit[6].location.Y = Y;//store Y position for future collision detection
			std::cout << (char)233;
		}
	}
	
	if(elapsedTime >= timePattern + 8)
	{
		//cout each individual enemy unit
		if(unit[7].active == true)
		{
			static int X = consoleSize.X - 10;
			static int Y = 0;

			if(elapsedTime >= timePattern + 12)
			{
				X = consoleSize.X - 10;
				Y = 0;
			}

			if(Y < consoleSize.Y - 1)//not reach player line
			{
				enemyUnitAi(&X, &Y);//pass the incrementing of X and Y to ai function
			}

			gotoXY(X, Y);
			unit[7].location.X = X;//store X position for future collision detection
			unit[7].location.Y = Y;//store Y position for future collision detection
			std::cout << (char)233;
		}

		if(unit[8].active == true)
		{
			static int X = consoleSize.X / 2 - 10;
			static int Y = 0;

			if(elapsedTime >= timePattern + 12)
			{
				X = consoleSize.X / 2 - 10;
				Y = 0;
			}

			if(Y < consoleSize.Y - 1)//not reach player line
			{
				enemyUnitAi(&X, &Y);//pass the incrementing of X and Y to ai function
			}

			gotoXY(X, Y);
			unit[8].location.X = X;//store X position for future collision detection
			unit[8].location.Y = Y;//store Y position for future collision detection
			std::cout << (char)233;
		}

		if(unit[9].active == true)
		{
			static int X = consoleSize.X / 2 + 10;
			static int Y = 0;

			if(elapsedTime >= timePattern + 12)
			{
				X = consoleSize.X / 2 + 10;
				Y = 0;
			}

			if(Y < consoleSize.Y - 1)//not reach player line
			{
				enemyUnitAi(&X, &Y);//pass the incrementing of X and Y to ai function
			}

			gotoXY(X, Y);
			unit[9].location.X = X;//store X position for future collision detection
			unit[9].location.Y = Y;//store Y position for future collision detection
			std::cout << (char)233;
		}

		if(unit[10].active == true)
		{
			static int X = consoleSize.X - 70;
			static int Y = 0;

			if(elapsedTime >= timePattern + 12)
			{
				X = consoleSize.X - 70;
				Y = 0;
			}

			if(Y < consoleSize.Y - 1)//not reach player line
			{
				enemyUnitAi(&X, &Y);//pass the incrementing of X and Y to ai function
			}

			gotoXY(X, Y);
			unit[10].location.X = X;//store X position for future collision detection
			unit[10].location.Y = Y;//store Y position for future collision detection
			std::cout << (char)233;
		}

		if(elapsedTime >= timePattern + 12)
		{
			timePattern += 12;
		}
	}
}

//enemy unit ai movement
void enemyUnitAi(int *X, int *Y)
{
	++*Y;
}

//collision detection here
void isEnemyAlive(double spawnTime)
{
	//all enemy units active first
	unit[0].active = true;
	unit[1].active = true;
	unit[2].active = true;
	unit[3].active = true;
	unit[4].active = true;
	unit[5].active = true;
	unit[6].active = true;
	unit[7].active = true;
	unit[8].active = true;
	unit[9].active = true;
	unit[10].active = true;
	
	//simulate enemy being shot(remove this whole loop if bullet collision is done)
	for(int i=0; i<=3; ++i)
	{
		if(elapsedTime >= spawnTime + 3)//if enemy unit shot in 3 sec
		{
			unit[i].active = false;
			//warning dispay stuff here
		}
	}

	//simulate enemy being shot(remove this whole loop if bullet collision is done)
	for(int i=4; i<=6; ++i)
	{
		if(elapsedTime >= spawnTime + 6)//if enemy unit shot in 3 sec
		{
			unit[i].active = false;
			//warning dispay stuff here
		}
	}

	//simulate enemy being shot(remove this whole loop if bullet collision is done)
	for(int i=7; i<=10; ++i)
	{
		if(elapsedTime >= spawnTime + 9)//if enemy unit shot in 3 sec
		{
			unit[i].active = false;
			//warning dispay stuff here
		}
	}
	
	//check if all units of the particular wave they spawn from is still alive
	if(unit[0].active == false && unit[1].active == false && unit[2].active == false && unit[3].active == false)
	{
		for(int i=0; i<=3; ++i)
		{
			unit[i].active = true;
		}
	}

	if(unit[4].active == false && unit[5].active == false && unit[6].active == false)
	{
		for(int i=4; i<=6; ++i)
		{
			unit[i].active = true;
		}
	}

	if(unit[7].active == false && unit[8].active == false && unit[9].active == false && unit[10].active == false) 
	{
		for(int i=7; i<=10; ++i)
		{
			unit[i].active = true;
		}
	}
} 