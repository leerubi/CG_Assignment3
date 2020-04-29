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
	
	void drawWall();


	void setPosX(float posX);
	void setPosY(float posY);
	void setPosZ(float posZ);
	//void setPose(int pose);
	//void setFront(int front);

	float getPosX();
	float getPosY();
	float getPosZ();
	//int getPose();
	//float getWidth();
	//float getHeight();
	//float getDepth();
	//int getFront();
};

