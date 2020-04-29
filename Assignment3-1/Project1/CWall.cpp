#include "CWall.h"

CWall::CWall()
{

}

CWall::CWall(float posX, float posY, float posZ)
{
	this->posX = posX;
	this->posX = posX;
	this->posX = posX;
}

CWall::~CWall()
{

}

void CWall::DrawWall()
{
	glLoadIdentity();
	glColor3f(0.0, 0.0, 0.0);
	
	////DJ
	//gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // left side
	////DJ
	glTranslatef(posX, posY - 0.2, posZ);

	// 1st column
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.2);
	for (int i = 0; i < 6; i++)
	{
		glTranslatef(0.0, -0.1, 0.0);
		glutSolidCube(0.1);
	}
	glPopMatrix();

	// 2nd column
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.1);
	for (int i = 0; i < 6; i++)
	{
		glTranslatef(0.0, -0.1, 0.0);

		if (pose == UP && i == 2)
			continue;
		if (pose == DOWN && i == 3)
			continue;
		if (pose == RIGHT && (i == 2 || i == 3))
			continue;

		glutSolidCube(0.1);
	}
	glPopMatrix();

	// 3rd column
	glPushMatrix();
	for (int i = 0; i < 6; i++)
	{
		glTranslatef(0.0, -0.1, 0.0);
		
		if (pose==UP && i==1)
			continue;
		if (pose == DOWN && i == 4)
			continue;
		if (pose == RIGHT && (i == 1 || i == 4))
			continue;
		if (pose == LEFT && (i == 1 || i == 4))
			continue;

		glutSolidCube(0.1);
	}
	glPopMatrix();

	// 4st column
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.1);
	for (int i = 0; i < 6; i++)
	{
		glTranslatef(0.0, -0.1, 0.0);

		if (pose == UP && i == 2)
			continue;
		if (pose == DOWN && i == 3)
			continue;
		if (pose == LEFT && (i == 2 || i == 3))
			continue;

		glutSolidCube(0.1);
	}
	glPopMatrix();

	// 5st column
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.2);
	for (int i = 0; i < 6; i++)
	{
		glTranslatef(0.0, -0.1, 0.0);
		glutSolidCube(0.1);
	}
	glPopMatrix();

	glLoadIdentity();

}

void CWall::SetPosX(float posX)
{
	this->posX = posX;
}

void CWall::SetPosY(float posY)
{
	this->posY = posY;
}

void CWall::SetPosZ(float posZ)
{
	this->posZ = posZ;
}

void CWall::SetPose(int pose)
{
	this->pose = pose;
}

float CWall::GetPosX()
{
	return posX;
}

float CWall::GetPosY()
{
	return posY;
}

float CWall::GetPosZ()
{
	return posZ;
}

int CWall::GetPose()
{
	return pose;
}
