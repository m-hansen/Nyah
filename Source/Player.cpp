#include "pch.h"

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
	mCollRect.width = 3 * PLAYER_WIDTH/4;
	mCollRect.height = 3 * PLAYER_HEIGHT/4;
	bulletManagerInstance = BulletManagerC::GetInstance();
}

// Update the player logic such as collisions, position, and animation frame references
void PlayerC::update(DWORD milliseconds)
{

	if (InputManagerC::GetInstance()->GetClockwiseRotationButton())
	{
		// Rotate the player clockwise
		mAngle += ANGLE_INCREMENT * (milliseconds/1000.0f);
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
		mAngle -= ANGLE_INCREMENT * (milliseconds/1000.0f);
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
	for (auto& bulletWave : bulletManagerInstance->getBulletWaves())
	{
		for (auto& bullet : bulletWave.getBullets())
		{
			if (!bullet.getIsAtCenter())
			{
				bool isGameOver = CollisionHandlerC::GetInstance()->CollisionOccuredRect(&mCollRect, bullet.getCollisionRectangle());
				if (isGameOver)
				{
					// Player collided with bullet, end game
					StateManagerC::GetInstance()->setState(StateManagerC::GAMEOVER);
					return;
				}
			}
		}
	}
}

// Move the player in a circle, update its collider position
void PlayerC::move(DWORD milliseconds)
{
	mPosition.x = sin(mAngle) * mRadius;
	mPosition.y = cos(mAngle) * mRadius;
	mCollRect.position.x = mPosition.x - mCollRect.width/2;
	mCollRect.position.y = mPosition.y - mCollRect.height/2;
}

// Render the player sprite
void PlayerC::render()
{
	GLfloat left = mPosition.x - mOrigin.x;
	GLfloat right = mPosition.x + mOrigin.x;
	GLfloat top = mPosition.y - mOrigin.y;
	GLfloat bottom = mPosition.y + mOrigin.y;

	GLfloat cleft = mCollRect.position.x;
	GLfloat cright = mCollRect.position.x + mCollRect.width;
	GLfloat ctop = mCollRect.position.y + mCollRect.height;
	GLfloat cbottom = mCollRect.position.y;

	SpriteManagerC::GetInstance()->renderPlayer(animationFrameNo, left, right, top, bottom);
	//SpriteManagerC::GetInstance()->renderCollisionRect(cleft, cbottom, cright, ctop, true);
}

// Return the player's collision rectangle
CollisionRectangle* PlayerC::getCollisionRectangle()
{
	return &mCollRect;
}