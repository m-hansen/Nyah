#include "pch.h"

#pragma region Wave Builder

BulletWaveC WaveBuilderC::operator()(float_t gapAngle, float_t gapSize, int32_t numBullets)
{
	BulletWaveC wave;

	int32_t initRadius = INITIAL_WAVE_RADIUS;

	BulletColor color = (BulletColor)getRangedRandom((int32_t)RED, (int32_t)MAX_COLOR);
	float_t x, y, z, theta;

	//create our list of bullets
	for (int32_t i = 0; i < numBullets; i++)
	{
		theta = (i * 360.0 / numBullets) * RADIANS;
		//make sure the angle along the circle is not in the range of the gap
		if (theta <= gapAngle || theta > gapAngle + gapSize)
		{
			//use polar coordinates to determine where along the circle to spawn the bullet
			x = initRadius * cos(theta);
			y = initRadius * sin(theta);
			wave.AddBullet(BulletC(x, y, cos(theta), sin(theta), BulletWaveC::sBulletRadius, color, theta));
		}
	}

	return wave;
}

BulletWaveC WaveBuilderC::operator()(bool clockwise)
{
	BulletWaveC wave;
	BulletColor color = (BulletColor)getRangedRandom((int32_t)RED, (int32_t)MAX_COLOR);
	float_t x, y, theta;

	//create our list of bullets
	int32_t initRadius = INITIAL_WAVE_RADIUS;
	for (int32_t i = 0; i < BulletWaveC::sNumBulletsSpiral; i++)
	{
		if (clockwise)
		{
			theta = (i * 360.0 / BulletWaveC::sNumBulletsRing) * RADIANS;
		}
		else
		{
			theta = ((BulletWaveC::sNumBulletsSpiral - i) * 360.0 / BulletWaveC::sNumBulletsRing) * RADIANS;
		}
		//use polar coordinates to determine where along the circle to spawn the bullet
		x = initRadius * cos(theta);
		y = initRadius * sin(theta);
		wave.AddBullet(BulletC(x, y, cos(theta), sin(theta), BulletWaveC::sBulletRadius, color, theta));
		initRadius += 40;
	}
	return wave;
}

#pragma endregion

BulletWaveC::BulletWaveC()
{
	mBullets = SList<BulletC>();
	mWaveAtCenter = false;
}

void BulletWaveC::AddBullet(BulletC bullet)
{
	mBullets.PushBack(bullet);
}


BulletWaveC::~BulletWaveC()
{

}

bool8_t BulletWaveC::getWaveAtCenter()
{
	return mWaveAtCenter;
}

void BulletWaveC::update(DWORD milliseconds, float_t velocity)
{
	for (auto& bullet : mBullets)
	{
		bullet.update(milliseconds, velocity);
	}

	if (!mBullets.IsEmpty())
	{
		if (mBullets.Front().getIsAtCenter())
		{
			mBullets.PopFront();
		}
	}
	else
	{
		mWaveAtCenter = true;
	}
}

void BulletWaveC::render()
{
	for (auto& bullet : mBullets)
	{
		bullet.render();
	}
}

SList<BulletC>& BulletWaveC::getBullets()
{
	return mBullets;
}