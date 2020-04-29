#pragma once
//�������� ��ݱ��� �ٸ�(�� ����� ��)

#include "global.h"
#include "CPlayerLeg.h"
class CPlayerThigh
{
private:
	float jointX;
	float jointY;
	float length;
	float width;
	float angle;
	long startTick;
	long currentTick;
	bool direction;
	
	int passCount;

	CPlayerLeg leftLeg;
	CPlayerLeg rightLeg;
public :
	CPlayerThigh();

	void setJoint(float jointX, float jointY);

	void setAngle(float angle);
	float getAngle();

	void drawThigh(float positionX, float positionY, int type);

	void setPassCount(int passCount);
};

