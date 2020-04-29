#pragma once
#include "global.h"

class CWall
{
private:
	int pose;
	float posX=0;
	float posY=0;
	float posZ=0;
	float width; // x in MC
	float height; // y in MC
	float depth; // z in MC
	int front;

public:
	CWall();
	CWall(float posX, float posY, float posZ);
	~CWall();
	
	void DrawWall();

	void SetPosX(float posX);
	void SetPosY(float posY);
	void SetPosZ(float posZ);
	void SetPose(int pose);
	//void setFront(int front);

	float GetPosX();
	float GetPosY();
	float GetPosZ();
	int GetPose();
	//float getWidth();
	//float getHeight();
	//float getDepth();
	//int getFront();
};

