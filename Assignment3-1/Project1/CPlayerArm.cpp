#include "CPlayerArm.h"
#include <iostream>
using namespace std;
CPlayerArm::CPlayerArm()
{
	jointX = 0;
	jointY = 0;

	length = 0.4;
	width = 0.1;

	leftAngle = 0;
	rightAngle = 0;

	leftPreviousAngle = 0;
	rightPreviousAngle = 0;

	leftRotateAngle = 0;
	rightRotateAngle = 0;
}

void CPlayerArm::setJoint(float jointX, float jointY)
{
	this->jointX = jointX;
	this->jointY = jointY;
}


void CPlayerArm::drawArm(float positionX, float positionY, int type)
{

	//rightRotateAngle = 1;
	if(leftRotateAngle!=leftAngle)
		leftRotateAngle = leftPreviousAngle += (leftAngle - leftPreviousAngle)*0.1;

	if (rightRotateAngle != rightAngle)
		rightRotateAngle = rightPreviousAngle += (rightAngle - rightPreviousAngle)*0.1;

	jointX = positionX;
	jointY = positionY;
	switch (type)
	{
	case LEFT:
		//model-frame
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(jointX, jointY, 0);
		glRotatef(leftRotateAngle, 0, 0, 1);

		glBegin(GL_POLYGON);
		glColor3f(0.7, 0.7, 0.0);
			glVertex2f(0, 0);
			glVertex2f(width, -width);
			glVertex2f(width, -length + width);
			glVertex2f(0, -length);
			glVertex2f(-width, -length + width);
			glVertex2f(-width, -width);
		glEnd();


		leftForeArm.drawForeArm(length, LEFT);
		glLoadIdentity();
		glPopMatrix();
		break;
	case RIGHT:
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(jointX, jointY, 0);


		//for(float i = rightPreviousAngle; i == rightAngle; i+= (rightAngle - rightPreviousAngle) * 0.01)
		glRotatef(rightRotateAngle, 0, 0, 1);
		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 0.0);
			glVertex2f(0, 0);
			glVertex2f(width, -width);
			glVertex2f(width, -length + width);
			glVertex2f(0, -length);
			glVertex2f(-width, -length + width);
			glVertex2f(-width, -width);
		glEnd();
		rightForeArm.drawForeArm(length, RIGHT);
		glLoadIdentity();
		glPopMatrix();
		break;
	default:
		break;
	}
	//glutSwapBuffers();
}

void CPlayerArm::setMotion(int pose)
{
	leftPreviousAngle = leftAngle;
	rightPreviousAngle = rightAngle;
	switch (pose) {
	case RED:
		//���� 0, ������ 0
		leftAngle = 0;
		rightAngle = 0;
		break;
	case BLUE:
		//���� 180, ������ 90
		leftAngle = 180;
		rightAngle = 90;
		break;
	case GREEN:
		//���� 180, ������ 180
		leftAngle = 180;
		rightAngle = 180;
		break;
	case YELLOW:
		//���� 90, ������ -90
		leftAngle = 90;
		rightAngle = -90;
		break;
	default:
		//RED
		leftAngle = 0;
		rightAngle = 0;
		break;
	}

	leftForeArm.setMotion(pose);
	rightForeArm.setMotion(pose);
}