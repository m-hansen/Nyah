#include <windows.h>
#include "baseTypes.h"
#include "GameTime.h"

GameTimeC* GameTimeC::sInstance = NULL;

GameTimeC* GameTimeC::CreateInstance()
{
	if (sInstance != NULL) { return sInstance; }
	else { sInstance = new GameTimeC(); }
	return sInstance;
}

void GameTimeC::reset()
{
	mCurrentTime = 0;
	mIsRunning = false;
}

void GameTimeC::pause()
{
	mIsRunning = false;
}

void GameTimeC::start()
{
	mIsRunning = true;
}

void GameTimeC::update(DWORD milliseconds)
{
	if (mIsRunning)
	{
		mCurrentTime += milliseconds;
	}
}

DWORD GameTimeC::getCurrentTime()
{
	return mCurrentTime;
}

DWORD GameTimeC::getCurrentTimeInSeconds()
{
	DWORD timeInSeconds = (mCurrentTime / 1000);
	return timeInSeconds;
}