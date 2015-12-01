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
#include "UIManager.h"
#include "SoundManager.h"
#include "CollisionHandler.h"
#include "Player.h"

// Declarations
const char8_t CGame::mGameTitle[]="Nyah";
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
	StateManagerC::CreateInstance();
	InputManagerC::CreateInstance();
	SpriteManagerC::CreateInstance();
	BulletManagerC::CreateInstance();
	UIManagerC::CreateInstance();
	SoundManagerC::CreateInstance();
	PlayerC::CreateInstance();
	CollisionHandlerC::CreateInstance();

	InputManagerC::GetInstance()->init();
	BulletManagerC::GetInstance()->init();
	StateManagerC::GetInstance()->setState(StateManagerC::TITLE);
	SpriteManagerC::GetInstance()->init();
	UIManagerC::GetInstance()->init();
	SoundManagerC::GetInstance()->init();
	PlayerC::GetInstance()->init();
}

void CGame::reset()
{
	BulletManagerC::GetInstance()->shutdown();
	BulletManagerC::GetInstance()->reset();

	BulletManagerC::CreateInstance();
	BulletManagerC::GetInstance()->init();
	PlayerC::GetInstance()->init();
	StateManagerC::GetInstance()->setState(StateManagerC::PLAYING);

	SoundManagerC::GetInstance()->reset();
	UIManagerC::GetInstance()->reset();
}

void CGame::UpdateFrame(DWORD milliseconds)			
{
	keyProcess();
//	InputManagerC::GetInstance()->update(milliseconds);

	// Update frame, regardless of state
	SpriteManagerC::GetInstance()->update(milliseconds);
	
	switch (StateManagerC::GetInstance()->getState())
	{
		case StateManagerC::TITLE:
			if (InputManagerC::GetInstance()->GetStartButton())
			{
				StateManagerC::GetInstance()->setState(StateManagerC::PLAYING);
				SoundManagerC::GetInstance()->playSelectSFX();
				SoundManagerC::GetInstance()->playBGM();
			}
			break;
		case StateManagerC::PLAYING:
			BulletManagerC::GetInstance()->updateBullets(milliseconds);
			PlayerC::GetInstance()->update(milliseconds);
			UIManagerC::GetInstance()->update(milliseconds);
			if (InputManagerC::GetInstance()->GetResetButton())
			{
				CGame::GetInstance()->reset();
			}
			if (InputManagerC::GetInstance()->DebugPlayerKill())
			{
				StateManagerC::GetInstance()->setState(StateManagerC::GAMEOVER);
			}
			break;
		case StateManagerC::GAMEOVER:
			if (InputManagerC::GetInstance()->GetResetButton())
			{
				CGame::GetInstance()->reset();
			}
			if (InputManagerC::GetInstance()->GetBackButton())
			{
				StateManagerC::GetInstance()->setState(StateManagerC::TITLE);
			}
			break;
	}
	
}

void CGame::DrawScene(void)											
{
	startOpenGLDrawing();

	// Render, regardless of state
	SpriteManagerC::GetInstance()->renderBackground();
	
	switch (StateManagerC::GetInstance()->getState())
	{
		case StateManagerC::TITLE:
			UIManagerC::GetInstance()->renderLogo();
			break;
		case StateManagerC::PLAYING:
			BulletManagerC::GetInstance()->renderSprites();
			PlayerC::GetInstance()->render();
			UIManagerC::GetInstance()->renderScore();
			break;
		case StateManagerC::GAMEOVER:
			UIManagerC::GetInstance()->renderGameOver();
			UIManagerC::GetInstance()->renderScore();
			break;
	}
}

CGame *CGame::CreateInstance()
{
	sInstance = new CGame();
	return sInstance;
}

void CGame::shutdown()
{
	StateManagerC::GetInstance()->shutdown();
	BulletManagerC::GetInstance()->shutdown();
	SoundManagerC::GetInstance()->shutdown();
}

void CGame::DestroyGame(void)
{
	delete StateManagerC::GetInstance();	
	delete SpriteManagerC::GetInstance();
	delete BulletManagerC::GetInstance();
	delete PlayerC::GetInstance();
	delete InputManagerC::GetInstance();
	delete SoundManagerC::GetInstance();
	delete UIManagerC::GetInstance();
}