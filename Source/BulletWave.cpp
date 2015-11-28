//#include <assert.h>
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
#include "collinfo.h"
#include "object.h"
#include "Bullet.h"
#include "BulletWave.h"
#include "random.h"

BulletWaveC::BulletWaveC()
{
	float_t missingArcStartAngle = getRangedRandom(0, 270);
	BulletColor color = (BulletColor)getRangedRandom((int)RED, (int)MAX);
	missingArcStartAngle *= RADIANS;
	float_t x, y, theta;
	bulletPtrs = (BulletC**)malloc(NUM_BULLETS * sizeof(BulletC*));
	numBullets = 0;
	for (int i = 0; i < NUM_BULLETS; i++)
	{
		bulletPtrs[i] = NULL;
		theta = (i * 360.0 / NUM_BULLETS) * RADIANS;
		if (theta <= missingArcStartAngle || theta > missingArcStartAngle + (PI/2.0f))
		{
			x = 3000.0f * cos(theta);
			y = 3000.0f * sin(theta);
			bulletPtrs[i] = new BulletC(x, y, VELOCITY * cos(theta), VELOCITY * sin(theta), BULLET_RADIUS, color);
			if (numBullets == 0)
				firstBullet = bulletPtrs[i];
			numBullets++;
		}
	}
	waveAtCenter = false;
}

BulletWaveC::~BulletWaveC()
{
	for (uint32_t i = 0; i< NUM_BULLETS; ++i)
	{
		if(bulletPtrs[i] != NULL)
			delete bulletPtrs[i];
	}
	free(bulletPtrs);
}

bool8_t BulletWaveC::getWaveAtCenter()
{
	return waveAtCenter;
}

void BulletWaveC::update(DWORD milliseconds)
{
	for (uint32_t i = 0; i<NUM_BULLETS; ++i)
	{
		if (bulletPtrs[i] != NULL)
			bulletPtrs[i]->update(milliseconds);
	}
	if (firstBullet->getIsAtCenter())
	{
		waveAtCenter = true;
	}
}

void BulletWaveC::render()
{
	for (uint32_t i = 0; i< NUM_BULLETS; ++i)
	{
		if (bulletPtrs[i] != NULL)
			bulletPtrs[i]->render();
	}
}