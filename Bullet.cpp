#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <gl/glut.h>
#include "baseTypes.h"
#include "ShapeDraw.h"
#include "collInfo.h"
#include "Object.h"
//#include "inputmapper.h"
#include "Bullet.h"
#include "field.h"
#include "fieldmanager.h"
#include "gamedefs.h"
#include "gameobjects.h"
#include "random.h"
#include "stateManager.h"
#include "inputmanager.h"

BulletC::BulletC(float initPosX, float initPosY, float initVelX, float initVelY, int id)
{

	mPosition.x = initPosX;
	mPosition.y = initPosY;
	mVelocity.x = initVelX;
	mVelocity.y = initVelY;

}

BulletC::~BulletC()
{
};

void BulletC::move()
{
	mPosition.x += mVelocity.x;
	mPosition.y += mVelocity.y;
}

void BulletC::update(DWORD milliseconds)
{
	move();
	doCollisions();
}

void BulletC::doCollisions()
{

}

void BulletC::render()
{

}

