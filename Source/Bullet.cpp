#include "pch.h"

BulletC::BulletC(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY, float_t radius, BulletColor color, float_t theta)
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
	mCollRect.position.x = mPosition.x;
	mCollRect.position.y = mPosition.y;
	mCollRect.width = 2 * mRadius/3;
	mCollRect.height = 2 * mRadius/3;
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

void BulletC::move(DWORD milliseconds, float_t velocity)
{
	if (animState == GLOWING)
	{
		mPosition.x += mVelocity.x * velocity * (milliseconds/1000.0f);
		mPosition.y += mVelocity.y * velocity * (milliseconds/1000.0f);
		mCollRect.position.x = mPosition.x - mCollRect.width/2;
		mCollRect.position.y = mPosition.y - mCollRect.height/2;
	}
}

void BulletC::update(DWORD milliseconds, float_t velocity)
{
	move(milliseconds, velocity);
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

	GLfloat cleft = mCollRect.position.x;
	GLfloat cright = mCollRect.position.x + mCollRect.width;
	GLfloat ctop = mCollRect.position.y + mCollRect.height;
	GLfloat cbottom = mCollRect.position.y;

	SpriteManagerC::GetInstance()->renderBullet(animState, mColor, animationFrameNo, left, right, top, bottom, mRadius);
	//SpriteManagerC::GetInstance()->renderCollisionRect(cleft, cbottom, cright, ctop, false);
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

