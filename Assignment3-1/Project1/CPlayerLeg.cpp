#include "CPlayerLeg.h"

CPlayerLeg::CPlayerLeg()
{
	jointX = 0;
	jointY = 0;

	width = 0.1;
	length = 0.5;

	rightAngle = -45;
	leftAngle = -45;

	startTick = GetTickCount64();

	rightDirection = 0;
	leftDirection = 0;

	rightCircuit = false;
}

void CPlayerLeg::drawLeg(float tightLength, int type, 
	float thighJointX, float thighJointY, int thighAngle, bool thighDirection)
{

	jointY = tightLength;
	switch (type)
	{
	case LEFT:
		setLeftAngle(thighDirection, thighAngle);
		//model-frame
		glPushMatrix();
		glTranslatef(jointX, -jointY, 0);
		glRotatef(leftAngle, 0, 0, 1);
		glBegin(GL_POLYGON);
			glColor3f(0.0, 0.7, 0.7);
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
		setRightAngle(thighDirection, thighAngle);
		//���������� ��ǥ ����(���⼭�� ������ Arm�� joint
		glPushMatrix();
		//������ joint�� �������� �󸶸�ŭ translation�� ����.
		glTranslatef(jointX, -jointY, 0);
		glRotatef(rightAngle, 0, 0, 1);
		glBegin(GL_POLYGON);
		glColor3f(0.0, 1.0, 1.0);
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

void CPlayerLeg::setLeftAngle(bool thighDirection, float thighAngle)
{
	//�Լ� ���ؼ� ���� thighDirection�� right �����̶� �ٲ㼭 ����
	thighDirection = !thighDirection;
	thighAngle = -thighAngle;

	if (thighDirection && thighAngle < 0) {
		//�߰����� �ڷ� ������ ����
		//�ִ�� ������ ���� ������ �����ϴ� �κ�
		leftDirection = 1;
	}

	if (thighDirection && thighAngle > 0) {
		//�տ��� �߰����� ������ ����
		//�߰����� ���� ����
		leftDirection = 2;
	}

	if (!thighDirection && thighAngle < 0) {
		//�ڿ��� �߰����� ������ ����
		//�߰����� ���� ����
		leftDirection = 3;
	}

	if (!thighDirection && thighAngle > 0) {
		//�߰����� ������ ������ ����
		//�ִ�� ������ ���� ������ �����ϴ� �κ�.
		leftDirection = 4;
	}


	switch (leftDirection) {
	case 1:
		startTick = GetTickCount64();
		leftAngle = -((startTick - currentTick) / (VELORATE - ADJUST * passCount));
		leftCircuit = true;
		break;
	case 2:
		currentTick = GetTickCount64();
		leftAngle = -45 + ((currentTick - startTick) / (VELORATE - ADJUST * passCount));

		break;
	case 3:
		currentTick = GetTickCount64();
		//startTick = GetTickCount64();
		leftAngle = -45 -((currentTick - startTick) / (VELORATE - ADJUST * passCount));
		break;
	case 4:
		startTick = GetTickCount64();
		leftAngle = -90 + ((startTick - currentTick) / (VELORATE - ADJUST * passCount));
		//leftCircuit = true;
		break;
	default:
		break;
	}
	//cout << leftDirection << " " << leftAngle << endl;

}

void CPlayerLeg::setRightAngle(bool thighDirection, float thighAngle)
{
	if (thighDirection && thighAngle < 0) {
		//�߰����� �ڷ� ������ ����
		//�ִ�� ������ ���� ������ �����ϴ� �κ�
		rightDirection = 1;
	}

	if (thighDirection && thighAngle > 0) {
		//�տ��� �߰����� ������ ����
		//�߰����� ���� ����
		rightDirection = 2;
	}

	if (!thighDirection && thighAngle < 0) {
		//�ڿ��� �߰����� ������ ����
		//�߰����� ���� ����
		rightDirection = 3;
	}

	if (!thighDirection && thighAngle > 0) {
		//�߰����� ������ ������ ����
		//�ִ�� ������ ���� ������ �����ϴ� �κ�.
		rightDirection = 4;
	}

	//cout << direction << endl;


	switch (rightDirection) {
	case 1:
		startTick = GetTickCount64();
		rightAngle = -((startTick - currentTick) / (VELORATE - ADJUST * passCount));
		break;
	case 2:
		currentTick = GetTickCount64();
		rightAngle = -45 + ((currentTick - startTick) / (VELORATE - ADJUST * passCount)) - 45 * rightCircuit;
		//cout << rightAngle << endl;

		break;
	case 3:
		startTick = GetTickCount64();
		rightAngle = -((startTick - currentTick) / (VELORATE - ADJUST * passCount));
		break;
	case 4:
		currentTick = GetTickCount64();
		rightAngle = -90 + ((currentTick - startTick) / (VELORATE - ADJUST * passCount));
		rightCircuit = true;
		break;
	default:
		break;
	}
}

void CPlayerLeg::setPassCount(int passCount)
{
	this->passCount = passCount;
}


