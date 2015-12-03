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
#include "PhaseManager.h"
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
	TIME_BETWEEN_RINGS = 1500;
	TIME_BETWEEN_SPIRALS = 4000;
	TIME_BETWEEN_WAVES = TIME_BETWEEN_RINGS;
	VELOCITY = -25;

	topOfBulletWaveList = NULL;
	topOfBulletWaveList = (BulletWaveListT*)malloc(sizeof(BulletWaveList));
	topOfBulletWaveList->nextBulletWave = NULL;
	hasStartedSpawning = false;
}

void BulletManagerC::spawnBulletWave()
{
	BulletWaveListT* currentBulletWave = topOfBulletWaveList;

	while (true)
	{
		if (currentBulletWave->nextBulletWave == NULL)
		{
			hasStartedSpawning = true;
			int32_t waveTypeChance = getRangedRandom(0, 10);
			BulletWaveType waveType;
			if (waveTypeChance > 7 && PhaseManagerC::GetInstance()->getPhase() >= NYAH_THREE)
			{
				waveType = SPIRAL;
				TIME_BETWEEN_WAVES = TIME_BETWEEN_SPIRALS;
			}
			else if(waveTypeChance > 6 && PhaseManagerC::GetInstance()->getPhase() >= NYAH_FOUR)
			{
				waveType = ZIGZAG;
				TIME_BETWEEN_WAVES = TIME_BETWEEN_SPIRALS;
			}
			else
			{
				waveType = RING;
				TIME_BETWEEN_WAVES = TIME_BETWEEN_RINGS;
			}
			currentBulletWave->bulletWavePtr = new BulletWaveC(VELOCITY, waveType);
			currentBulletWave->nextBulletWave = (BulletWaveListT*)malloc(sizeof(BulletWaveList));
			currentBulletWave = currentBulletWave->nextBulletWave;
			currentBulletWave->nextBulletWave = NULL;
			break;
		}
		else
		{
			currentBulletWave = currentBulletWave->nextBulletWave;
		}
	}
}

void BulletManagerC::shutdown()
{
	BulletWaveListT* currentBulletWave = topOfBulletWaveList;
	while (currentBulletWave->nextBulletWave != NULL)
	{
		BulletWaveListT* temp = currentBulletWave;
		delete temp->bulletWavePtr;
		currentBulletWave = currentBulletWave->nextBulletWave;
		free(temp);
	}
	topOfBulletWaveList = NULL;
}

void BulletManagerC::reset()
{
	delete sInstance;
	sInstance = NULL;
}

void BulletManagerC::renderSprites()
{
	BulletWaveListT* currentBulletWave = topOfBulletWaveList;
	while (currentBulletWave->nextBulletWave != NULL)
	{
		currentBulletWave->bulletWavePtr->render();
		currentBulletWave = currentBulletWave->nextBulletWave;
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
		if (TIME_BETWEEN_RINGS >= 700)
		{
			TIME_BETWEEN_RINGS -= 100;
			VELOCITY--;
		}
	}
	BulletWaveListT* currentBulletWave = topOfBulletWaveList;
	while (currentBulletWave->nextBulletWave != NULL)
	{
		currentBulletWave->bulletWavePtr->update(milliseconds);
		currentBulletWave = currentBulletWave->nextBulletWave;
	}

	if (topOfBulletWaveList->nextBulletWave != NULL)
	{
		if (topOfBulletWaveList->bulletWavePtr->getWaveAtCenter())
		{
			BulletWaveListT* temp = topOfBulletWaveList->nextBulletWave;
			delete topOfBulletWaveList->bulletWavePtr;
			free(topOfBulletWaveList);
			topOfBulletWaveList = temp;
		}
	}
}

BulletWaveListT* BulletManagerC::getClosestBulletWave()
{
	return topOfBulletWaveList;
}