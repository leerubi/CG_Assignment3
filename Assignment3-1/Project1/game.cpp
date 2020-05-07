#include "game.h"
using namespace std;

vector<CWall> walls; // 얘를 ASSN2때처럼 헤더파일에 선언하면 갑자기 오류나서 일단 여기로 옮김
MCIDEVICEID mID;

void glInit()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
}

void Initialize()
{
	sound.playsound(BGM);
	targetVelocity = initVelocity;
	startWallTimer = GetTickCount64();
	srand((unsigned int)time(NULL));
	walls.push_back(CWall(3, 0, 0));
	//thief.SetPose(LEFT);
	thief.SetPose(rand() % 5);

}

void DrawGround()
{
	//glColor3f(0.5, 0.5, 0.5);
	glTranslatef(-1.0, -1.9, 0.0);
	//glutWireCube(2);
	glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(0, 0, -1);
	glVertex3f(0, 0, 1);
	glVertex3f(20, 0, 1);
	glVertex3f(20, 0, -1);
	glEnd();

	glTranslatef(-1.0, 0, 0.0);
	glBegin(GL_QUADS);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1.1, 0);
	glVertex3f(10, 1.1, 0);
	glVertex3f(10, 0, 0);
	glEnd();
}

void PassWall()
{
	sound.playsound(PLAYERPASS);
	cout << "Pass" << endl;
	targetVelocity += 0.01;
	interval -= 300;
	prePlayerPosX = player.GetPosX();
	player.SetPassCnt(player.GetPassCnt() + 1);
	thief.SetPassCnt(thief.GetPassCnt() + 1);
	pass = true;
	previous++;
}

void FailWall()
{
	sound.playsound(PLAYERNONPASS);
	cout << "Fail" << endl;
	failCnt++;
	pass = false;
	previous++;

}

void MessageGameResult(bool success)
{
	HWND hwnd;
	HINSTANCE hInstance = GetModuleHandle(NULL);
	hwnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

	if (success) {
		sound.playsound(WIN);
		cout << "Win" << endl;
		MessageBoxA(hwnd, "Win", "Win", MB_OK);
	}
	else {
		sound.playsound(LOSE);
		cout << "Lose" << endl;
		MessageBoxA(hwnd, "Lose", "Lose", MB_OK);
	}

	exit(0);
}


void MyDisplay()
{
	//cout << "dis" << endl;
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (viewPoint == VP_PLAYER) {
		gluPerspective(120, -0.8, 0.1, 20.0);
		gluLookAt(player.GetPosX() + 0.1, player.GetPosY(), 0, player.GetPosX() + 0.15, player.GetPosY(), 0.0, 0.0, 0.5, 0.0); // left side
	}
	else {
		glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	}

	glMatrixMode(GL_MODELVIEW);
	DrawGround();
}

void SystemCheck() {

	//// DJ
	//CWall wall(0, 0, 0);
	//wall.SetPose(RIGHT);
	//wall.DrawWall();
	//// DJ

	// Wall - create a wall every "interval" time
	curWallTimer = GetTickCount64();

	if (curWallTimer - startWallTimer >= interval)
	{
		walls.push_back(CWall(3, 0, 0));
		startWallTimer = curWallTimer;
		total++;
	}

	// If the wall and the thief collide ...
	if (walls[now].GetPosX() < (thief.GetPosX() + 0.2)) // 0.2==thief torso radius
	{
		sound.playsound(THIEFPASS);

		// Wall - change to thief color
		walls[now].SetPose(thief.GetPose());

		// Thief - jump timer start
		if (walls[now].GetPose() == JUMP) {
			jumpThiefTimer = 0;
			jumpingThief = true;
		}

		// Thief - change to new color
		//thief.SetPose(LEFT);
		thief.SetPose(rand() % 5);
		now++;
	}

	// If the wall and the player collide ...
	if (walls[previous].GetPosX() <= (player.GetPosX() + 0.2)) // 0.2==player torso radius
	{
		// System - check if pass or fail
		if (cheatMode == ALL_PASS)
		{
			PassWall();
		}
		else if (cheatMode == ALL_FAIL)
		{
			FailWall();
		}
		else // cheatMode == NO
		{
			if (player.GetPose() == walls[previous].GetPose())
				PassWall();
			else
				FailWall();
		}
	}

	// System - WIN if the distance between player and thief is less than a "threshold"
	//"threshold" == player.getPlayerSize()
	if (thief.GetPosX() <= player.GetPosX() + 0.2) // 0.2==player torso radius
		MessageGameResult(true);

	// System - LOSE if failCnt >= 3
	if (failCnt >= 3)
		MessageGameResult(false);

	////System - LOSE after 3 minutes in all pass mode
	if ((cheatMode == ALL_PASS) && (GetTickCount64() - allPassTimer > 1000 * 60 * 3))
		MessageGameResult(false);

	//System - LOSE if the player is out of the view
	if (player.GetPosX() < -1.0)
		MessageGameResult(false);

	glutPostRedisplay();
}

void Animation(int value) {
	//gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0); // front
	//gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // left side
	//gluLookAt(0.5, 0.5, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0); // diagonal

	curVelocity = targetVelocity;

	// Player - running animation
	player.DrawCharacter();

	// Player - jump animation
	jumpPlayerTimer++;
	if (jumpPlayerTimer < (initVelocity / curVelocity * 20) && jumpingPlayer)
	{
		player.SetPosX(player.GetPosX() - curVelocity / 15.0f);
		player.SetPosY(player.GetPosY() + curVelocity * 4.0f);
	}
	else if (jumpPlayerTimer < (initVelocity / curVelocity * 80) && jumpingPlayer)
	{
		player.SetPosX(player.GetPosX() - curVelocity / 15.0f);
	}
	else if (jumpPlayerTimer < (initVelocity / curVelocity * 100) && jumpingPlayer)
	{
		player.SetPosX(player.GetPosX() - curVelocity / 15.0f);
		player.SetPosY(player.GetPosY() - curVelocity * 4.0f);
	}
	else if (jumpingPlayer)
	{
		player.SetPosY(-0.4);
		player.SetPose(DEFAULT);
		jumpingPlayer = false;
	}

	// Player - moving animation towards the thief
	if (pass) {

		player.SetPosX(player.GetPosX() + 0.01);
		if ((player.GetPosX() - prePlayerPosX) >= 0.1) {
			prePlayerPosX = 0.0;
			pass = false;
			//cameraZoomIn();
		}
	}

	// Thief - running animation with random pose
	thief.DrawCharacter();
	// set thief pose randomly

	// Thief - jump animation
	jumpThiefTimer++;
	if (jumpThiefTimer < (initVelocity / curVelocity * 20) && jumpingThief)
	{
		thief.SetPosX(thief.GetPosX() - curVelocity / 15.0f);
		thief.SetPosY(thief.GetPosY() + curVelocity * 4.0f);
	}
	else if (jumpThiefTimer < (initVelocity / curVelocity * 80) && jumpingThief)
	{
		thief.SetPosX(thief.GetPosX() - curVelocity / 15.0f);
	}
	else if (jumpThiefTimer < (initVelocity / curVelocity * 100) && jumpingThief)
	{
		thief.SetPosX(thief.GetPosX() - curVelocity / 15.0f);
		thief.SetPosY(thief.GetPosY() - curVelocity * 4.0f);
	}
	else if (jumpingThief)
	{
		thief.SetPosY(-0.4);
		jumpingThief = false;
	}

	// Wall - moving animation
	for (int i = front; i < total; i++)
	{
		// set wall pose
		walls[i].SetPosX(walls[i].GetPosX() - curVelocity);
		//cout << walls[i].GetPosX() << endl;
		walls[i].DrawWall();
		if (walls[i].GetPosX() + 0.1 < -1.0)
		{
			walls[i].SetPosX(-1.0 - 0.1); // out of window
			front = i;
		}
	}

	glutPostRedisplay();
	glutSwapBuffers();
	glutTimerFunc(1, Animation, 1);
}

void MySpecialKey(int key, int x, int y) {
	sound.playsound(CHANGE);
	switch (key) {
	case GLUT_KEY_LEFT:
		player.SetPose(LEFT);
		break;
	case GLUT_KEY_RIGHT:
		player.SetPose(RIGHT);
		break;
	case GLUT_KEY_UP:
		player.SetPose(UP);
		break;
	case GLUT_KEY_DOWN:
		player.SetPose(DOWN);
		break;
	}

	glutPostRedisplay();
}

void MyKey(unsigned char key, int x, int y) {


	switch (key)
	{
	case 'b':
		if (viewPoint == VP_GLOBAL) {
			//3인칭 시점이었다면 1인칭으로 변환
			viewPoint = VP_PLAYER;
		}
		else {
			//1인칭이었다면 3인칭으로 변환
			viewPoint = VP_GLOBAL;
		}
		return;
	case 32: // Space bar
		if (!jumpingPlayer)
		{
			sound.playsound(CHANGE);
			player.SetPose(JUMP);
			jumpPlayerTimer = 0;
			jumpingPlayer = true;
		}
		return;
	}

	switch (key)
	{
	case 'c':
		if (cheatMode == ALL_PASS)
			cheatMode = NO;
		else
			cheatMode = ALL_PASS;
		break;
	case 'f':
		if (cheatMode == ALL_FAIL)
			cheatMode = NO;
		else
			cheatMode = ALL_FAIL;
		break;

	}

	if (cheatMode == ALL_PASS)
	{
		cout << "All Pass Mode" << endl;
		allPassTimer = GetTickCount64();
	}
	else if (cheatMode == ALL_FAIL)
		cout << "All Fail Mode" << endl;
	else
		cout << "No Cheat" << endl;

	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);
	glInit();

	Initialize();
	glutDisplayFunc(MyDisplay);
	//glutReshape
	glutIdleFunc(SystemCheck);
	glutTimerFunc(0, Animation, 1);
	glutSpecialFunc(MySpecialKey);
	glutKeyboardFunc(MyKey);

	glutMainLoop();
}

/*
void cameraZoomIn() {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(currentVelocity * 25, 10, 0, (10 - currentVelocity * 25) * 0.7f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(int w, int h) {
	width = w;
	height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(currentVelocity * 25, 10, 0, (10 - currentVelocity * 25) * 0.7f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
*/
