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
#include "CollisionRectangle.h"
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
	/*mCollRect.x = mPosition.x;
	mCollRect.y = mPosition.y;
	mCollRect.width = PLAYER_WIDTH;
	mCollRect.height = PLAYER_HEIGHT;*/
}

void PlayerC::update(DWORD milliseconds)
{

	if (InputManagerC::GetInstance()->GetClockwiseRotationButton())
	{
		mAngle += ANGLE_INCREMENT;
		move(milliseconds);
	}

	if (InputManagerC::GetInstance()->GetCounterClockwiseRotationButton())
	{
		mAngle -= ANGLE_INCREMENT;
		move(milliseconds);
	}

}

void PlayerC::move(DWORD milliseconds)
{
	mPosition.x = mOrigin.x + sin(mAngle) * mRadius;
	mPosition.y = mOrigin.y + cos(mAngle) * mRadius;
	/*mCollRect.x = mPosition.x;
	mCollRect.y = mPosition.y;*/
}

void PlayerC::render()
{
	GLfloat left = mPosition.x - mOrigin.x;
	GLfloat right = mPosition.x + mOrigin.x;
	GLfloat top = mPosition.y - mOrigin.y;
	GLfloat bottom = mPosition.y + mOrigin.y;

	SpriteManagerC::GetInstance()->renderPlayer(left, right, top, bottom);
}
//
//CollisionRectangle* PlayerC::getCollisionRectangle()
//{
//	return &mCollRect;
//}