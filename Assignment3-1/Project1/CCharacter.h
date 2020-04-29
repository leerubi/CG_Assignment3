#pragma once
#include "global.h"

class CCharacter
{
private:
	GLUquadricObj* obj;
	bool flag = true;
	int pose = DEFAULT;
	float posX;
	float posY;
	float posZ;
	int passCnt = 0;

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

	// Draw methods
	void DrawArm(int direction);
	void DrawForearm(int direction);
	void DrawBody();
	void DrawThigh(int direction);
	void DrawLeg(int direction);
	void DrawCharacter();
	void ChangeWireOrSolid(bool flag);

	// Get & Set methods
	int GetPose();
	float GetPosX();
	float GetPosY();
	int GetPassCnt();

	void SetPose(int pose);
	void SetPosX(float posX);
	void SetPosY(float posY);
	void SetPassCnt(int passCnt);

};

