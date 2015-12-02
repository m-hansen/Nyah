//#include <assert.h>
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
#include "Bullet.h"
#include "BulletWave.h"
#include "random.h"

BulletWaveC::BulletWaveC(int32_t VELOCITY, BulletWaveType waveType)
{
	switch (waveType)
	{
		case SPIRAL: createSpiral(VELOCITY); break;
		case RING: createRing(VELOCITY); break;
		case ZIGZAG: createZigZagRing(VELOCITY); break;
	}
}

void BulletWaveC::createRing(int32_t VELOCITY)
{
	float_t missingArcStartAngle = getRangedRandom(0, 270) * RADIANS;
	BulletColor color = (BulletColor)getRangedRandom((int32_t)RED, (int32_t)MAX_COLOR);
	float_t x, y, theta;

	//create our list of bullets
	topOfBulletList = NULL;
	topOfBulletList = (BulletListT*)malloc(sizeof(BulletList));
	BulletListT* currentBullet = topOfBulletList;
	currentBullet->nextBullet = NULL;
	int32_t initRadius = INITIAL_WAVE_RADIUS;
	for (int32_t i = 0; i < NUM_BULLETS; i++)
	{
		theta = (i * 360.0 / NUM_BULLETS) * RADIANS;
		//make sure the angle along the circle is not in the range of the gap
		if (theta <= missingArcStartAngle || theta > missingArcStartAngle + (PI / 2.0f))
		{
			//use polar coordinates to determine where along the circle to spawn the bullet
			x = initRadius * cos(theta);
			y = initRadius * sin(theta);
			currentBullet->bulletPtr = new BulletC(x, y, VELOCITY * cos(theta), VELOCITY * sin(theta), BULLET_RADIUS, color, theta);
			currentBullet->nextBullet = (BulletListT*)malloc(sizeof(BulletList));
			currentBullet = currentBullet->nextBullet;
		}
	}
	currentBullet->nextBullet = NULL;
	waveAtCenter = false;
}

void BulletWaveC::createZigZagRing(int32_t VELOCITY)
{
	float_t missingArcStartAngle = 90 * RADIANS;
	BulletColor color = (BulletColor)getRangedRandom((int32_t)RED, (int32_t)MAX_COLOR);
	float_t x, y, theta;

	//create our list of bullets
	topOfBulletList = NULL;
	topOfBulletList = (BulletListT*)malloc(sizeof(BulletList));
	BulletListT* currentBullet = topOfBulletList;
	currentBullet->nextBullet = NULL;
	int32_t initRadius = INITIAL_WAVE_RADIUS;
	for (int32_t i = 0; i < NUM_BULLETS; i++)
	{
		theta = (i * 360.0 / NUM_BULLETS) * RADIANS;
		//make sure the angle along the circle is not in the range of the gap
		if (theta <= missingArcStartAngle || theta > missingArcStartAngle + (PI/2.0f))
		{
		//use polar coordinates to determine where along the circle to spawn the bullet
			x = initRadius * cos(theta);
			y = initRadius * sin(theta);
			currentBullet->bulletPtr = new BulletC(x, y, VELOCITY * cos(theta), VELOCITY * sin(theta), BULLET_RADIUS, color, theta);
			currentBullet->nextBullet = (BulletListT*)malloc(sizeof(BulletList));
			currentBullet = currentBullet->nextBullet;
		}
	}

	initRadius += 600;
	missingArcStartAngle = 215 * RADIANS;
	color = (BulletColor)getRangedRandom((int32_t)RED, (int32_t)MAX_COLOR);
	for (int32_t i = 0; i < NUM_BULLETS; i++)
	{
		theta = (i * 360.0 / NUM_BULLETS) * RADIANS;
		//make sure the angle along the circle is not in the range of the gap
		if (theta <= missingArcStartAngle || theta > missingArcStartAngle + (PI / 2.0f))
		{
			//use polar coordinates to determine where along the circle to spawn the bullet
			x = initRadius * cos(theta);
			y = initRadius * sin(theta);
			currentBullet->bulletPtr = new BulletC(x, y, VELOCITY * cos(theta), VELOCITY * sin(theta), BULLET_RADIUS, color, theta);
			currentBullet->nextBullet = (BulletListT*)malloc(sizeof(BulletList));
			currentBullet = currentBullet->nextBullet;
		}
	}

	initRadius += 600;
	missingArcStartAngle = 90 * RADIANS;
	color = (BulletColor)getRangedRandom((int32_t)RED, (int32_t)MAX_COLOR);
	for (int32_t i = 0; i < NUM_BULLETS; i++)
	{
		theta = (i * 360.0 / NUM_BULLETS) * RADIANS;
		//make sure the angle along the circle is not in the range of the gap
		if (theta <= missingArcStartAngle || theta > missingArcStartAngle + (PI / 2.0f))
		{
			//use polar coordinates to determine where along the circle to spawn the bullet
			x = initRadius * cos(theta);
			y = initRadius * sin(theta);
			currentBullet->bulletPtr = new BulletC(x, y, VELOCITY * cos(theta), VELOCITY * sin(theta), BULLET_RADIUS, color, theta);
			currentBullet->nextBullet = (BulletListT*)malloc(sizeof(BulletList));
			currentBullet = currentBullet->nextBullet;
		}
	}

	initRadius += 600;
	missingArcStartAngle = 215 * RADIANS;
	color = (BulletColor)getRangedRandom((int32_t)RED, (int32_t)MAX_COLOR);
	for (int32_t i = 0; i < NUM_BULLETS; i++)
	{
		theta = (i * 360.0 / NUM_BULLETS) * RADIANS;
		//make sure the angle along the circle is not in the range of the gap
		if (theta <= missingArcStartAngle || theta > missingArcStartAngle + (PI / 2.0f))
		{
			//use polar coordinates to determine where along the circle to spawn the bullet
			x = initRadius * cos(theta);
			y = initRadius * sin(theta);
			currentBullet->bulletPtr = new BulletC(x, y, VELOCITY * cos(theta), VELOCITY * sin(theta), BULLET_RADIUS, color, theta);
			currentBullet->nextBullet = (BulletListT*)malloc(sizeof(BulletList));
			currentBullet = currentBullet->nextBullet;
		}
	}

	currentBullet->nextBullet = NULL;
	waveAtCenter = false;
}

void BulletWaveC::createSpiral(int32_t VELOCITY)
{
	int32_t directionChance = getRangedRandom(0, 2);
	BulletColor color = (BulletColor)getRangedRandom((int32_t)RED, (int32_t)MAX_COLOR);
	float_t x, y, theta;

	//create our list of bullets
	topOfBulletList = NULL;
	topOfBulletList = (BulletListT*)malloc(sizeof(BulletList));
	BulletListT* currentBullet = topOfBulletList;
	currentBullet->nextBullet = NULL;
	int32_t initRadius = INITIAL_WAVE_RADIUS;
	for (int32_t i = 0; i < NUM_BULLETS_SPIRAL; i++)
	{
		if (directionChance == 0)
		{
			theta = (i * 360.0 / NUM_BULLETS) * RADIANS;
		}
		else
		{
			theta = ((NUM_BULLETS_SPIRAL - i) * 360.0 / NUM_BULLETS) * RADIANS;
		}
		//use polar coordinates to determine where along the circle to spawn the bullet
		x = initRadius * cos(theta);
		y = initRadius * sin(theta);
		currentBullet->bulletPtr = new BulletC(x, y, VELOCITY * cos(theta), VELOCITY * sin(theta), BULLET_RADIUS, color, theta);
		currentBullet->nextBullet = (BulletListT*)malloc(sizeof(BulletList));
		currentBullet = currentBullet->nextBullet;
		initRadius += 30;
	}
	currentBullet->nextBullet = NULL;
	waveAtCenter = false;
}

BulletWaveC::~BulletWaveC()
{
	BulletListT* currentBullet = topOfBulletList;
	while (currentBullet->nextBullet != NULL)
	{
		BulletListT* temp = currentBullet;
		delete temp->bulletPtr;
		currentBullet = currentBullet->nextBullet;
		free(temp);
	}
	topOfBulletList = NULL;
}

bool8_t BulletWaveC::getWaveAtCenter()
{
	return waveAtCenter;
}

void BulletWaveC::update(DWORD milliseconds)
{
	BulletListT* currentBullet = topOfBulletList;
	while (currentBullet->nextBullet != NULL)
	{
		currentBullet->bulletPtr->update(milliseconds);
		currentBullet = currentBullet->nextBullet;
	}
	if (topOfBulletList->nextBullet != NULL)
	{
		if (topOfBulletList->bulletPtr->getIsAtCenter())
		{
			BulletListT* temp = topOfBulletList->nextBullet;
			delete topOfBulletList->bulletPtr;
			free(topOfBulletList);
			topOfBulletList = temp;
		}
	}
	else
	{
		waveAtCenter = true;
	}
}

void BulletWaveC::render()
{
	BulletListT* currentBullet = topOfBulletList;
	while (currentBullet->nextBullet != NULL)
	{
		currentBullet->bulletPtr->render();
		currentBullet = currentBullet->nextBullet;
	}
}

BulletListT* BulletWaveC::getTopOfBulletList()
{
	return topOfBulletList;
}