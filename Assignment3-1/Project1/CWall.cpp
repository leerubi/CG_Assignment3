#include "CWall.h"

CWall::CWall()
{

}

void CWall::drawWall()
{
	glLoadIdentity();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(posX, posY-0.2, posZ);

	glPushMatrix();
	for (int i = 0; i < 6; i++)
	{
		glTranslatef(0.0, -0.1, 0.0);
		glutSolidCube(0.1);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.1);
	for (int i = 0; i < 6; i++)
	{
		glTranslatef(0.0, -0.1, 0.0);
		glutSolidCube(0.1);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.1);
	for (int i = 0; i < 6; i++)
	{
		glTranslatef(0.0, -0.1, 0.0);
		glutSolidCube(0.1);
	}
	glPopMatrix();
	glLoadIdentity();

}



CWall::CWall(float posX, float posY, float posZ)
{
	this->posX = posX;
	this->posX = posX;
	this->posX = posX;
	drawWall();
}

CWall::~CWall()
{

}


void CWall::setPosX(float posX)
{
	this->posX = posX;
}

void CWall::setPosY(float posY)
{
	this->posY = posY;
}

void CWall::setPosZ(float posZ)
{
	this->posZ = posZ;
}

float CWall::getPosX()
{
	return posX;
}

float CWall::getPosY()
{
	return posY;
}

float CWall::getPosZ()
{
	return posZ;
}
