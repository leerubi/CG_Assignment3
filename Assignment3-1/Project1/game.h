#pragma once
#pragma comment(lib, "winmm")

#define STB_IMAGE_IMPLEMENTATION
#include "global.h"
#include "CCharacter.h"
#include "CWall.h"
#include "CSound.h"
#include <Windows.h>
#include <tchar.h>
#include <math.h>
#include <ctime>
#include <mmsystem.h>
#include "stb_image.h"
CONST TCHAR* lpszClass = _T("Message Box!\n");

// Game objects
CCharacter player(-0.5, -0.4, 0);
CCharacter thief(0.5, -0.4, 0);
//vector<CWall> walls;


// Timer variables
int startWallTimer = 0;
int curWallTimer = 0;










//CSound sound;

//Wall indices
int total = 0;		//Number of walls
int front = 0;		//Index of the leftmost wall
int previous = 0;	//Index of the wall just to the right of player
int now = 0;		//Index of the wall just to the left of theif

//System varables
int passCount = 0;		 //Number of pass
int failCount = 0;		 //Number of fail
int interval = 3000;	 //Wall creation interval
float initVelocity = 0.02f; //Wall initial velocity
float currentVelocity;		//Wall current velocity
float velocity;				//Wall new velocity

//Timer variables
int startTickCount = 0;
int currentTickCount = 0;
int allPassTimer = 0;

//Jump variables
int jumpThiefTimer = 0;
int jumpPlayerTimer = 0;
bool jumpingThief = false;
bool jumpingPlayer = false;

//Player animation variables
bool pass = false;
float playerDistance = 0.1f;
float previousPlayerPosition = 0.0f;

//Cheatcode variables
enum CheatMode
{
	NO,
	ALL_PASS,
	ALL_FAIL
};
CheatMode cheatMode;

//Window variables
int width;
int height;

//Functions
void init();					// Initialize game states
void setObjectColor(int color);	// Set theif or wall pose(color)
void cameraZoomIn();			// Camera zoom-in
void message(bool success);		// End the game and show the message if pass or fail
void playSound();				// Play background or effect sound

//Input callback functions
void display();		// Display game objects (player, theif, wall, & ground)
void reshape(int w, int h); // reshape callback
void doSystemCheck();	//  Game system update
void doAnimation(int value);	// Player, thief, wall animation update
void selectPose(int key, int x, int y);	// Select player pose using keyboard input
void doKeyboard(unsigned char Key, int x, int y); // Selec cheat mode using keyboard input
