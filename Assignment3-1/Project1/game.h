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
#include <iostream>
using namespace std;
CONST TCHAR* lpszClass = _T("Message Box!\n");

// Game objects
CCharacter player(-0.5, -0.4, 0);
CCharacter thief(0.5, -0.4, 0);
//vector<CWall> walls;
CSound sound;

// Wall indices
int total = 0;		// Number of walls
int front = 0;		// Index of the leftmost wall
int previous = 0;	// Index of the wall just to the right of player
int now = 0;		// Index of the wall just to the left of theif

// Wall creation timers
int startWallTimer = 0;
int curWallTimer = 0;

// Wall velocities
float initVelocity = 0.01;  // Wall initial velocity
float curVelocity;			// Wall current velocity
float targetVelocity;		// Wall next velocity

// Jump variables
int jumpThiefTimer = 0;
int jumpPlayerTimer = 0;
bool jumpingThief = false;
bool jumpingPlayer = false;

// Cheatmode variable
int cheatMode = NO;
int allPassTimer = 0;

// System varables
int failCnt = 0;		 // Number of fail
int interval = 3000;	 // Wall creation interval

// Player movement variables
bool pass = false;
float prePlayerPosX;


int viewPoint = VP_GLOBAL;


//// Functions
//void init();					// Initialize game states
//void setObjectColor(int color);	// Set theif or wall pose(color)
//void cameraZoomIn();			// Camera zoom-in
//void message(bool success);		// End the game and show the message if pass or fail
//void playSound();				// Play background or effect sound
//
////Input callback functions
//void MyDisplay();		// Display game objects (player, theif, wall, & ground)
//void reshape(int w, int h); // reshape callback
//void doSystemCheck();	//  Game system update
//void doAnimation(int value);	// Player, thief, wall animation update
//void MySpecialKey(int key, int x, int y);	// Select player pose using keyboard input
//void doKeyboard(unsigned char Key, int x, int y); // Selec cheat mode using keyboard input
