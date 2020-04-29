#include "CCharacter.h"

CCharacter::CCharacter()
{
}

CCharacter::CCharacter(float posX, float posY, float posZ)
{
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;
}

CCharacter::~CCharacter()
{
}

void CCharacter::DrawArm(int direction)
{
	if (curAngleLeftArm != targetAngleLeftArm)
		curAngleLeftArm = preAngleLeftArm += (targetAngleLeftArm - preAngleLeftArm) * 0.1;

	if (curAngleRightArm != targetAngleRightArm)
		curAngleRightArm = preAngleRightArm += (targetAngleRightArm - preAngleRightArm) * 0.1;

	switch (direction)
	{
	case LEFT_SIDE:
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		obj = gluNewQuadric();
		//glRotatef(angle, x, y, z);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glTranslatef(0.2, 0.0, 0.0); // Joint 위치로 이동
		glRotatef(curAngleLeftArm, 0.0, 1.0, 0.0);
		ChangeWireOrSolid(flag);
		gluCylinder(obj, 0.05, 0.05, 0.2, 50, 1);
		//glPopMatrix();

		break;

	case RIGHT_SIDE:
		glPushMatrix();
		glColor3f(0.0, 1.0, 0.0);
		obj = gluNewQuadric();
		//glRotatef(angle, x, y, z);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glTranslatef(-0.2, 0.0, 0.0); // Joint 위치로 이동
		glRotatef(curAngleRightArm, 0.0, 1.0, 0.0);
		ChangeWireOrSolid(flag);
		gluCylinder(obj, 0.05, 0.05, 0.2, 50, 1);
		//glPopMatrix();

		break;
	}
}

void CCharacter::DrawForearm(int direction)
{
	switch (direction)
	{
	case LEFT_SIDE:
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		obj = gluNewQuadric();
		glTranslatef(0.0, 0.0, 0.2); // Joint 위치로 이동
		ChangeWireOrSolid(flag);
		gluCylinder(obj, 0.05, 0.05, 0.2, 50, 1);
		glPopMatrix();
		glPopMatrix();

		break;

	case RIGHT_SIDE:
		glPushMatrix();
		glColor3f(0.0, 1.0, 0.0);
		obj = gluNewQuadric();
		glTranslatef(0.0, 0.0, 0.2); // Joint 위치로 이동
		ChangeWireOrSolid(flag);
		gluCylinder(obj, 0.05, 0.05, 0.2, 50, 1);
		glPopMatrix();
		glPopMatrix();

		break;
	}
}

void CCharacter::DrawBody()
{
	// Torso
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	obj = gluNewQuadric();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	ChangeWireOrSolid(flag);
	gluCylinder(obj, 0.2, 0.15, 0.4, 50, 1);
	glPopMatrix();

	// Neck
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	obj = gluNewQuadric();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, -0.05); // Joint 위치로 이동
	ChangeWireOrSolid(flag);
	gluCylinder(obj, 0.05, 0.05, 0.05, 50, 1);
	glPopMatrix();

	// Head
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	obj = gluNewQuadric();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, -0.25); // Joint 위치로 이동
	ChangeWireOrSolid(flag);
	gluCylinder(obj, 0.1, 0.1, 0.2, 50, 1);
	glPopMatrix();

}

void CCharacter::DrawThigh(int direction)
{
	if (angleThigh > 45)
		forward = true;
	if (angleThigh < -45)
		forward = false;

	if (forward)
	{
		curThighTimer = GetTickCount64();
		//angleThigh = 45 - ((curThighTimer - startThighTimer) / (VELORATE - ADJUST));
		angleThigh = 45 - ((curThighTimer - startThighTimer) / (VELORATE / (passCnt+1)));
	}
	else
	{
		startThighTimer = GetTickCount64();
		//angleThigh = - 45 - ((curThighTimer - startThighTimer) / (VELORATE - ADJUST));
		angleThigh = - 45 - ((curThighTimer - startThighTimer) / (VELORATE / (passCnt+1)));

	}

	switch (direction)
	{
	case LEFT_SIDE:
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		obj = gluNewQuadric();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glTranslatef(0.1, 0.0, 0.40); // Joint 위치로 이동
		glRotatef(angleThigh, 1, 0, 0);
		ChangeWireOrSolid(flag);
		gluCylinder(obj, 0.05, 0.05, 0.2, 50, 1);
		//glPopMatrix();

		break;

	case RIGHT_SIDE:
		glPushMatrix();
		glColor3f(0.0, 1.0, 0.0);
		obj = gluNewQuadric();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glTranslatef(-0.1, 0.0, 0.40); // Joint 위치로 이동
		glRotatef(-angleThigh, 1, 0, 0);
		ChangeWireOrSolid(flag);
		gluCylinder(obj, 0.05, 0.05, 0.2, 50, 1);
		//glPopMatrix();

		break;
	}
}

void CCharacter::DrawLeg(int direction)
{
	if (angleThigh  > 0)
	{
		//angleLeftLeg = 0;
		angleLeftLeg = -(angleThigh / 2);
		angleRightLeg = angleThigh / 2;
	}
	else
	{
		angleLeftLeg = angleThigh / 2;
		angleRightLeg = -(angleThigh / 2);

	}

	switch (direction)
	{
	case LEFT_SIDE:
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		obj = gluNewQuadric();
		glTranslatef(0.0, 0.0, 0.2); // Joint 위치로 이동
		glRotatef(angleLeftLeg, 1, 0, 0);
		ChangeWireOrSolid(flag);
		gluCylinder(obj, 0.05, 0.05, 0.2, 50, 1);
		glPopMatrix();
		glPopMatrix();

		break;

	case RIGHT_SIDE:
		glPushMatrix();
		glColor3f(0.0, 1.0, 0.0);
		obj = gluNewQuadric();
		glTranslatef(0.0, 0.0, 0.2); // Joint 위치로 이동
		glRotatef(-angleRightLeg, 1, 0, 0);
		ChangeWireOrSolid(flag);
		gluCylinder(obj, 0.05, 0.05, 0.2, 50, 1);
		glPopMatrix();
		glPopMatrix();

		break;
	}
}

void CCharacter::DrawCharacter()
{
	glLoadIdentity();
	////DJ
	//gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // left side
	////DJ
	glTranslatef(posX, posY, posZ);
	glRotatef(-90, 0, 1, 0);
	glScalef(0.5, 0.5, 0.5);
	DrawBody();
	DrawArm(RIGHT_SIDE);
	DrawForearm(RIGHT_SIDE);
	DrawArm(LEFT_SIDE);
	DrawForearm(LEFT_SIDE);
	DrawThigh(RIGHT_SIDE);
	DrawLeg(RIGHT_SIDE);
	DrawThigh(LEFT_SIDE);
	DrawLeg(LEFT_SIDE);
}

void CCharacter::ChangeWireOrSolid(bool flag)
{
	if (flag)
		gluQuadricDrawStyle(obj, GLU_LINE);
}

void CCharacter::SetPose(int pose) {
	
	this->pose = pose;
	preAngleLeftArm = targetAngleLeftArm;
	preAngleRightArm = targetAngleRightArm;

	switch (pose)
	{
	case LEFT: // LEFT
		targetAngleLeftArm = 135;
		targetAngleRightArm = 135;
		break;
	case RIGHT: // RIGHT
		targetAngleLeftArm = -135;
		targetAngleRightArm = -135;
		break;
	case UP: // UP
		targetAngleLeftArm = 180;
		targetAngleRightArm = 180;
		break;
	case DOWN: // DOWN
		targetAngleLeftArm = 90;
		targetAngleRightArm = -90;
		break;
	}
}

void CCharacter::SetPosX(float posX)
{
	this->posX = posX;
}

void CCharacter::SetPosY(float posY)
{
	this->posY = posY;
}

void CCharacter::SetPassCnt(int passCnt)
{
	this->passCnt = passCnt;
}

int CCharacter::GetPose()
{
	return pose;
}

float CCharacter::GetPosX()
{
	return posX;
}

float CCharacter::GetPosY()
{
	return posY;
}

int CCharacter::GetPassCnt()
{
	return passCnt;
}


