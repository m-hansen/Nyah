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
#include "object.h"
//#include "inputmapper.h"
#include "SpriteManager.h"
#include "bullet.h"
#include "field.h"
#include "fieldmanager.h"
#include "gamedefs.h"
#include "gameobjects.h"
#include "random.h"
#include "stateManager.h"
#include "inputmanager.h"

BulletC::BulletC(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY, float_t radius, BulletColor color)
{

	mPosition.x = initPosX;
	mPosition.y = initPosY;
	mVelocity.x = initVelX;
	mVelocity.y = initVelY;
	mRadius = radius;
	animationFrameNo = 0;
	isAtCenter = false;
	mColor = color;
	animState = GLOWING;
	mCollRect.position.x = mPosition.x + mRadius;
	mCollRect.position.y = mPosition.y + mRadius;
	mCollRect.width = mRadius;
	mCollRect.height = mRadius;
}

BulletC::BulletC()
{

	mPosition.x = 0.0f;
	mPosition.y = 0.0f;
	mVelocity.x = 1.0f;
	mVelocity.y = 1.0f;
	mRadius = 20.0f;
	animationFrameNo = 0;
	isAtCenter = false;

};

BulletC::~BulletC()
{
};

void BulletC::move(DWORD milliseconds)
{
	if (animState == GLOWING)
	{
		float deltaTime = ((mCurrentTime + milliseconds) - mLastUpdateTime) / 1000.0f;
		mPosition.x += mVelocity.x * deltaTime;
		mPosition.y += mVelocity.y * deltaTime;
		mCollRect.position.x = mPosition.x + mRadius;
		mCollRect.position.y = mPosition.y + mRadius;
	}
}

void BulletC::update(DWORD milliseconds)
{
	move(milliseconds);
	doCollisions();
	updateAnimationFrame(milliseconds);
}

void BulletC::doCollisions()
{
	if (mPosition.x < THRESHOLD && mPosition.x > -THRESHOLD
		&& mPosition.y < THRESHOLD && mPosition.y > -THRESHOLD
		&& animState != SHRINKING)
	{
		animState = SHRINKING;
		animationFrameNo = 0;
	}
}

bool8_t BulletC::getIsAtCenter()
{
	return isAtCenter;
}

void BulletC::render()
{
	GLfloat left = mPosition.x;
	GLfloat right = mPosition.x + (mRadius * 2.0f);
	GLfloat top = mPosition.y;
	GLfloat bottom = mPosition.y + (mRadius * 2.0f);
	SpriteManagerC::GetInstance()->renderBullet(animState, mColor, animationFrameNo, left, right, top, bottom, mRadius);
}

void BulletC::updateAnimationFrame(DWORD milliseconds)
{
	mCurrentTime += milliseconds;

	if (mCurrentTime - mLastUpdateTime > ANIMATION_FRAME_UPDATE_DELTA_TIME)
	{
		mLastUpdateTime = mCurrentTime;
		if (animState == GLOWING)
		{
			if (animationFrameNo < 7)
				animationFrameNo++;
			else
				animationFrameNo = 0;
		}
		else if (animState == SHRINKING)
		{
			if (animationFrameNo < 4)
				animationFrameNo++;
			else
				isAtCenter = true;
		}
	}
}

CollisionRectangle* BulletC::getCollisionRectangle()
{
	return &mCollRect;
}

