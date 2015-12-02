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

// Initialize the player's position and bounding box
void PlayerC::init()
{
	mVelocity.x = 0.0f;
	mVelocity.y = 0.0f;
	mAngle = 0.0f;
	mRadius = INITIAL_RADIUS;
	mPosition.x = 0.0f;
	mPosition.y = mRadius;
	mOrigin.x = PLAYER_WIDTH / 2;
	mOrigin.y = PLAYER_HEIGHT / 2;
	animationFrameNo = 0;
	rotateAnimationDirection = 1;
	mCollRect.position.x = mPosition.x;
	mCollRect.position.y = mPosition.y;
	mCollRect.width = PLAYER_WIDTH;
	mCollRect.height = PLAYER_HEIGHT;
	bulletManagerInstance = BulletManagerC::GetInstance();
}

// Update the player logic such as collisions, position, and animation frame references
void PlayerC::update(DWORD milliseconds)
{

	if (InputManagerC::GetInstance()->GetClockwiseRotationButton())
	{
		// Rotate the player clockwise
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
		// Rotate the player counter-clockwise
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

// Check to see if the player has collided with an object
void PlayerC::checkForCollision()
{
	// Get a pointer to each bullet wave
	BulletWaveListT* bulletWaves = bulletManagerInstance->getClosestBulletWave();
	if (!bulletManagerInstance->getHasStartedSpawning())
	{
		return;
	}

	// Iterate over each bullet wave, starting with the closest wave
	while (bulletWaves->nextBulletWave != NULL)
	{
		BulletListT* topOfBulletList = bulletWaves->bulletWavePtr->getTopOfBulletList();

		while (topOfBulletList->nextBullet != NULL)
		{
			// Iterate over each bullet in the wave
			BulletC* bullet = topOfBulletList->bulletPtr;
			bool isGameOver = CollisionHandlerC::GetInstance()->CollisionOccuredRect(&mCollRect, bullet->getCollisionRectangle());
			if (isGameOver)
			{
				// Player collided with bullet, end game
				StateManagerC::GetInstance()->setState(StateManagerC::GAMEOVER);
				return;
			}

			topOfBulletList = topOfBulletList->nextBullet;
		}

		bulletWaves = bulletWaves->nextBulletWave;
	}
}

// Move the player in a circle, update its collider position
void PlayerC::move(DWORD milliseconds)
{
	mPosition.x = mOrigin.x + sin(mAngle) * mRadius;
	mPosition.y = mOrigin.y + cos(mAngle) * mRadius;
	mCollRect.position.x = mPosition.x;
	mCollRect.position.y = mPosition.y;
}

// Render the player sprite
void PlayerC::render()
{
	GLfloat left = mPosition.x - mOrigin.x;
	GLfloat right = mPosition.x + mOrigin.x;
	GLfloat top = mPosition.y - mOrigin.y;
	GLfloat bottom = mPosition.y + mOrigin.y;

	SpriteManagerC::GetInstance()->renderPlayer(animationFrameNo, left - PLAYER_WIDTH/2, right - PLAYER_WIDTH/2, top - PLAYER_HEIGHT/2, bottom - PLAYER_HEIGHT/2);
}

// Return the player's collision rectangle
CollisionRectangle* PlayerC::getCollisionRectangle()
{
	return &mCollRect;
}