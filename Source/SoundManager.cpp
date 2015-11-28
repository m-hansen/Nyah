#include <assert.h>
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>	
#include "SoundManager.h"

SoundManagerC* SoundManagerC::sInstance = NULL;

SoundManagerC *SoundManagerC::CreateInstance()
{
	if (sInstance != NULL)return sInstance;
	else

		sInstance = new SoundManagerC();
	return sInstance;
}

void SoundManagerC::reset()
{
	releaseSound(bgm);
	createSound(&bgm, "./Sounds/bgm.wav");
}

void SoundManagerC::shutdown()
{
	releaseSound(bgm);
	m_pSystem->release();
}

void SoundManagerC::init()
{
	//FMOD initializing related code
	if (FMOD::System_Create(&m_pSystem) != FMOD_OK)
	{
		return;
	}
	int driverCount = 0;
	m_pSystem->getNumDrivers(&driverCount);
	if (driverCount == 0)
	{
		return;
	}
	m_pSystem->init(36, FMOD_INIT_NORMAL, NULL);

	//create sound effects
	createSound(&bgm, "./Sounds/bgm.wav");
}

void SoundManagerC::createSound(FMOD::Sound **pSound, const char* pFile)
{
	m_pSystem->createSound(pFile, FMOD_HARDWARE, 0, pSound);
}

void SoundManagerC::playSound(FMOD::Sound *pSound, bool bLoop)
{
	if (!bLoop)
	{
		pSound->setMode(FMOD_LOOP_OFF);
	}
	else
	{
		pSound->setMode(FMOD_LOOP_NORMAL);
		pSound->setLoopCount(-1);
	}
	m_pSystem->playSound(FMOD_CHANNEL_FREE, pSound, false, 0);
}

void SoundManagerC::releaseSound(FMOD::Sound *pSound)
{
	pSound->release();
}

void SoundManagerC::playBGM()
{
	playSound(bgm, true);
}