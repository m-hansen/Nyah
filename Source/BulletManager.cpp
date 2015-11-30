#include <assert.h>
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl/glut.h>
#include <gl/gl.h>												// Header File For The OpenGL32 Library
#include <gl/glu.h>												// Header File For The GLu32 Library
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "collinfo.h"
#include "object.h"
#include "BulletWave.h"
#include "BulletManager.h"
#include "random.h"

BulletManagerC* BulletManagerC::sInstance = NULL;

BulletManagerC *BulletManagerC::CreateInstance()
{
	if (sInstance != NULL) { return sInstance; }
	else { sInstance = new BulletManagerC(); }
	return sInstance;
}

void BulletManagerC::init()
{
	TIME_BETWEEN_WAVES = 1500;
	VELOCITY = -25;
	bulletWavePtrs = (BulletWaveC**)malloc(MAX_NUM_WAVES * sizeof(BulletWaveC*));
	for (int32_t i = 0; i < MAX_NUM_WAVES; i++)
	{
		bulletWavePtrs[i] = NULL;
	}
}

void BulletManagerC::spawnBulletWave()
{
	for (int32_t i = 0; i < MAX_NUM_WAVES; i++)
	{
		if (bulletWavePtrs[i] == NULL)
		{
			bulletWavePtrs[i] = new BulletWaveC(VELOCITY);
			break;
		}
	}
}

void BulletManagerC::shutdown()
{
	for (uint32_t i = 0; i < MAX_NUM_WAVES; ++i)
	{
		if (bulletWavePtrs[i] != NULL)
		{
			delete bulletWavePtrs[i];
		}
	}
	free(bulletWavePtrs);
}

void BulletManagerC::reset()
{
	delete sInstance;
	sInstance = NULL;
}

void BulletManagerC::renderSprites()
{
	for (uint32_t i = 0; i < MAX_NUM_WAVES; ++i)
	{
		if (bulletWavePtrs[i] != NULL)
		{
			bulletWavePtrs[i]->render();
		}
	}
}

void BulletManagerC::updateBullets(DWORD milliseconds)
{
	mCurrentTime += milliseconds;
	if (mCurrentTime - mLastSpawnTime > TIME_BETWEEN_WAVES)
	{
		mLastSpawnTime = mCurrentTime;
		spawnBulletWave();
	}
	if (mCurrentTime - mLastSpeedIncreaseTime > INCREASE_SPAWN_SPEED_DELTA_TIME)
	{
		mLastSpeedIncreaseTime = mCurrentTime;
		if (TIME_BETWEEN_WAVES >= 700)
		{
			TIME_BETWEEN_WAVES -= 150;
			VELOCITY--;
		}
	}
	for (uint32_t i = 0; i < MAX_NUM_WAVES; ++i)
	{
		if (bulletWavePtrs[i] != NULL)
		{
			bulletWavePtrs[i]->update(milliseconds);
			if (bulletWavePtrs[i]->getWaveAtCenter())
			{
				delete(bulletWavePtrs[i]);
				bulletWavePtrs[i] = NULL;
			}
		}
	}
}