#pragma once
#include "global.h"

class CCharacter
{
private:
	GLUquadricObj* obj;
	bool flag = true;
	int pose;
	float posX;
	float posY;
	float posZ;

	// Arm
	float preAngleLeftArm;
	float preAngleRightArm;
	float curAngleLeftArm = 0;
	float curAngleRightArm = 0;
	float targetAngleLeftArm; 
	float targetAngleRightArm;

	// Thigh
	long startThighTimer = GetTickCount64();
	long curThighTimer;
	bool forward = true; 
	float angleThigh = 0;

	// Leg
	float angleLeftLeg = 0;
	float angleRightLeg = 0;


public:
	CCharacter();
	CCharacter(float posX, float posY, float posZ);
	~CCharacter();
	void drawArm(int direction);
	void drawForearm(int direction);
	void drawBody();
	void drawThigh(int direction);
	void drawLeg(int direction);
	void drawCharacter();
	void changeWireOrSolid(bool flag);
	void setPose(int pose);

};

