#define GAME_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <gl\glut.h>
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "collInfo.h"
#include "object.h"
#include "ball.h"
#include "field.h"
#include "random.h"
#include "gameObjects.h"
#include "openGLStuff.h"
#include "game.h"
#include "StateManager.h"
#include "BallManager.h"
#include "FieldManager.h"
#include "InputManager.h"
#include "SpriteManager.h"
#include "BulletManager.h"

// Declarations
const char8_t CGame::mGameTitle[]="Framework1";
CGame* CGame::sInstance=NULL;
BOOL Initialize (GL_Window* window, Keys* keys)					// Any OpenGL Initialization Goes Here
{
	initOpenGLDrawing(window,keys,0.0f, 0.0f, 0.0f);
	CGame::CreateInstance();
	CGame::GetInstance()->init();
	return TRUE;						
}

void CGame::init()
{
	//BallManagerC::CreateInstance();
	StateManagerC::CreateInstance();
	FieldManagerC::CreateInstance();
	InputManagerC::CreateInstance();
	SpriteManagerC::CreateInstance();
	BulletManagerC::CreateInstance();

	InputManagerC::GetInstance()->init();

	//BallManagerC::GetInstance()->init();
	BulletManagerC::GetInstance()->init();
	StateManagerC::GetInstance()->setState(StateManagerC::HALF_BALLS_FILLED);
	FieldManagerC::GetInstance()->init();
	SpriteManagerC::GetInstance()->init();
}
void CGame::UpdateFrame(DWORD milliseconds)			
{
	keyProcess();
	//SpriteManagerC::GetInstance()->updateSprites(milliseconds);
	BulletManagerC::GetInstance()->updateBullets(milliseconds);
	//BallManagerC::GetInstance()->updateBalls(milliseconds);
//	InputManagerC::GetInstance()->update(milliseconds);
}

void CGame::DrawScene(void)											
{
	startOpenGLDrawing();
	SpriteManagerC::GetInstance()->renderBackground();
	//BallManagerC::GetInstance()->renderBalls();
	BulletManagerC::GetInstance()->renderSprites();
	FieldManagerC::GetInstance()->renderField();
}


CGame *CGame::CreateInstance()
{
	sInstance = new CGame();
	return sInstance;
}
void CGame::shutdown()
{
	//BallManagerC::GetInstance()->shutdown();
	StateManagerC::GetInstance()->shutdown();
	FieldManagerC::GetInstance()->shutdown();
	BulletManagerC::GetInstance()->shutdown();
	//SpriteManagerC::GetInstance()->shutdown();
}
void CGame::DestroyGame(void)
{
	delete BallManagerC::GetInstance();	
	delete StateManagerC::GetInstance();	
	delete FieldManagerC::GetInstance();	
	delete SpriteManagerC::GetInstance();
}