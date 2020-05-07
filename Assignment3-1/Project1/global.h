#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>

//player, thief pose and wall color
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
#define JUMP 4
#define DEFAULT 5

//sound track
#define BGM 5
#define THIEFPASS 6
#define PLAYERPASS 7
#define PLAYERNONPASS 8
#define WIN 9
#define LOSE 10
#define CHANGE 11

//left, right
#define LEFT_SIDE 12
#define RIGHT_SIDE 13

//cheatmode
#define NO 14
#define ALL_PASS 15
#define ALL_FAIL 16

//leg, thigh velocity rate
//velocity is faster if it is smaller
#define VELORATE 20

//view point
#define VP_PLAYER 21
#define VP_GLOBAL 22