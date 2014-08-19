#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

extern StopWatch g_timer;
extern bool g_quitGame;

enum Keys
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
	K_SPACE,
    K_COUNT
};

void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory
void renderEnemy();			// renders enemy
void trackBullet();			//track bullet

//enemy
struct enemy
{
	short X;//enemy unit X coor.
	int velocity;//enemy velocity
	bool right;//move right
	bool left;//move left
	bool forward;//move forward
	bool forwardRight;//move digonally right
	bool forwardLeft;//move diagonally left
};

#endif // _GAME_H