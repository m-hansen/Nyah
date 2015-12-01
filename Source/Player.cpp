#include <stdlib.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <Windows.h>
#include <math.h>
#include "baseTypes.h"
#include "collInfo.h"
#include "Object.h"
#include "SpriteManager.h"
#include "InputManager.h"
#include "CollisionHandler.h"
#include "BulletManager.h"
#include "BulletWave.h"
#include "Bullet.h"
#include "StateManager.h"
#include "Player.h"

PlayerC *PlayerC::sInstance = NULL;

PlayerC *PlayerC::CreateInstance()
{
	if (sInstance != NULL) { return sInstance; }
	else { sInstance = new PlayerC(); }
	return sInstance;
}

void PlayerC::init()
{
	mPosition.x = 0.0f;
	mPosition.y = 0.0f;
	mVelocity.x = 0.0f;
	mVelocity.y = 0.0f;
	mAngle = 0.0f;
	mRadius = INITIAL_RADIUS;
	mOrigin.x = PLAYER_WIDTH / 2;
	mOrigin.y = PLAYER_HEIGHT / 2;
	animationFrameNo = 0;
	rotateAnimationDirection = 1;
	mCollRect.position.x = mPosition.x + (PLAYER_WIDTH / 2);
	mCollRect.position.y = mPosition.y + (PLAYER_HEIGHT / 2);
	mCollRect.width = 1;
	mCollRect.height = 1;
	bulletManagerInstance = BulletManagerC::GetInstance();
}

void PlayerC::update(DWORD milliseconds)
{

	if (InputManagerC::GetInstance()->GetClockwiseRotationButton())
	{
		mAngle += ANGLE_INCREMENT;
		move(milliseconds);
		rotateAnimationDirection = 1;
		animationFrameNo += rotateAnimationDirection;
		if (animationFrameNo > LAST_ANIM_FRAME)
		{
			animationFrameNo = FIRST_ANIM_FRAME;
		}
	}

	if (InputManagerC::GetInstance()->GetCounterClockwiseRotationButton())
	{
		mAngle -= ANGLE_INCREMENT;
		move(milliseconds);
		rotateAnimationDirection = -1;
		animationFrameNo += rotateAnimationDirection;
		if (animationFrameNo < FIRST_ANIM_FRAME)
		{
			animationFrameNo = LAST_ANIM_FRAME;
		}
	}

	checkForCollision();
}

void PlayerC::checkForCollision()
{
	BulletWaveListT* closestWave = bulletManagerInstance->getClosestBulletWave();
	if (!bulletManagerInstance->getHasStartedSpawning())
	{
		return;
	}
	BulletListT* topOfBulletList = closestWave->bulletWavePtr->getTopOfBulletList();

	while (topOfBulletList->nextBullet != NULL)
	{
		BulletC* bullet = topOfBulletList->bulletPtr;
		bool isGameOver = CollisionHandlerC::GetInstance()->CollisionOccuredRect(&mCollRect, bullet->getCollisionRectangle());
		if (isGameOver)
		{
			StateManagerC::GetInstance()->setState(StateManagerC::GAMEOVER);
			return;
		}
		
		topOfBulletList = topOfBulletList->nextBullet;
	}
}

void PlayerC::move(DWORD milliseconds)
{
	mPosition.x = mOrigin.x + sin(mAngle) * mRadius;
	mPosition.y = mOrigin.y + cos(mAngle) * mRadius;
	mCollRect.position.x = mPosition.x + (PLAYER_WIDTH / 2);
	mCollRect.position.y = mPosition.y + (PLAYER_HEIGHT / 2);
}

void PlayerC::render()
{
	GLfloat left = mPosition.x - mOrigin.x;
	GLfloat right = mPosition.x + mOrigin.x;
	GLfloat top = mPosition.y - mOrigin.y;
	GLfloat bottom = mPosition.y + mOrigin.y;

	SpriteManagerC::GetInstance()->renderPlayer(animationFrameNo, left - PLAYER_WIDTH/2, right - PLAYER_WIDTH/2, top - PLAYER_HEIGHT/2, bottom - PLAYER_HEIGHT/2);
}

CollisionRectangle* PlayerC::getCollisionRectangle()
{
	return &mCollRect;
}