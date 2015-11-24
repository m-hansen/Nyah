#include <assert.h>
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>	// Header File For Variable Argument Routines
#include <math.h>	// Header File For Math Operations
#include <gl\gl.h>	// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <gl\glut.h>
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "collinfo.h"
#include "object.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "random.h"

BulletManagerC* BulletManagerC::sInstance = NULL;

BulletManagerC *BulletManagerC::CreateInstance()
{
	if (sInstance != NULL)return sInstance;
	else

		sInstance = new BulletManagerC();
	return sInstance;
}

void BulletManagerC::init()
{
	float_t x, y, theta;
	bulletPtrs = (BulletC**)malloc(NUM_BULLETS * sizeof(BulletC*));
	for (int i = 0; i < NUM_BULLETS; i++)
	{
		theta = ((i * 7.5) * 3.14159f) / 180.0f;
		x = 1600.0f * cos(theta);
		y = 1600.0f * sin(theta);
		bulletPtrs[i] = new BulletC(x, y, -1.0f * cos(theta), -1.0f * sin(theta), 100.0f);
	}
}

void BulletManagerC::shutdown()
{
	for (uint32_t i = 0; i<NUM_BULLETS; ++i)
	{
		delete bulletPtrs[i];
	}
	free(bulletPtrs);
}

void BulletManagerC::renderSprites()
{
	for (uint32_t i = 0; i<NUM_BULLETS; ++i)
	{
		bulletPtrs[i]->render();
	}
}

void BulletManagerC::updateBullets(DWORD milliseconds)
{
	for (uint32_t i = 0; i<NUM_BULLETS; ++i)
	{
		bulletPtrs[i]->update(milliseconds);
	}
}