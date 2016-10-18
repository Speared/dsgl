#include "FirstPersonControl.h"
//#include <gl\glut.h>
#include "Node.h"
#define DOWN 0x8000
//this dosn't work 
//TODO: fix it
#define PRESSED 1
#define STEP 0.1f
void FirstPersonControl::Update()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 1)
	{
		printf("Escape pressed. Get key down knoledge get!");
	}

	//arrow keys to move
	if (GetAsyncKeyState(VK_UP) & DOWN) {
		myNode->translation += myNode->forward * STEP;
	}

	if (GetAsyncKeyState(VK_DOWN) & DOWN) {
		myNode->translation += myNode->forward * -STEP;
	}

	if (GetAsyncKeyState(VK_LEFT) & DOWN) {
		myNode->translation += myNode->right * -STEP;
	}

	if (GetAsyncKeyState(VK_RIGHT) & DOWN) {
		myNode->translation += myNode->right * STEP;
	}

	//R/F to move up and down, becaus why not?
	if (GetAsyncKeyState('R') & DOWN) {
		myNode->translation += myNode->up * -STEP;
	}

	if (GetAsyncKeyState('F') & DOWN) {
		myNode->translation += myNode->up * STEP;
	}

	//WASD to turn
	if (GetAsyncKeyState('A') & DOWN) {
		myNode->rotation.y += 1;
	}

	if (GetAsyncKeyState('D') & DOWN) {
		myNode->rotation.y -= 1;
	}
	if (GetAsyncKeyState('W') & DOWN) {
		myNode->rotation.x -= 1;
	}

	if (GetAsyncKeyState('S') & DOWN) {
		myNode->rotation.x += 1;
	}
}


FirstPersonControl::FirstPersonControl()
{
	
}


FirstPersonControl::~FirstPersonControl()
{
}
