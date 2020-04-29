#include "CPlayerForearm.h"

CPlayerForearm::CPlayerForearm()
{
	jointX = 0;
	jointY = 0;

	width = 0.1;
	length = 0.3;

	leftAngle = 90;
	rightAngle = 90;

	leftPreviousAngle = 0;
	rightPreviousAngle = 0;

	leftRotateAngle = 0;
	rightRotateAngle = 0;

}

void CPlayerForearm::setJoint(float jointX, float jointY)
{
	this->jointX = jointX;
	this->jointY = jointY;
}

void CPlayerForearm::drawForeArm(float armLength, int type)
{
	if (leftRotateAngle != leftAngle)
		leftRotateAngle = leftPreviousAngle += (leftAngle - leftPreviousAngle) * 0.1;

	if (rightRotateAngle != rightAngle)
		rightRotateAngle = rightPreviousAngle += (rightAngle - rightPreviousAngle) * 0.1;


	jointY = armLength;
	switch (type)
	{
	case LEFT:
		//model-frame
		glPushMatrix();
		glTranslatef(jointX, -jointY, 0);
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
		glPopMatrix();
		break;
	case RIGHT:
		//���������� ��ǥ ����(���⼭�� ������ Arm�� joint
		glPushMatrix();

		//������ joint�� �������� �󸶸�ŭ translation�� ����.
		glTranslatef(jointX, -jointY, 0);
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
		glPopMatrix();
		break;
	default:
		break;
	}
}

void CPlayerForearm::setMotion(int pose)
{
	leftPreviousAngle = leftAngle;
	rightPreviousAngle = rightAngle;
	switch (pose) {
	case RED:
		//���� 90, ������ 90
		leftAngle = 90;
		rightAngle = 90;
		break;
	case BLUE:
		//���� 180, ������ 90
		leftAngle = 0;
		rightAngle = 0;
		break;
	case GREEN:
		//���� 180, ������ 180
		leftAngle = -45;
		rightAngle = 45;
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
}
