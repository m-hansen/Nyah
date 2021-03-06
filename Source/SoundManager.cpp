#include "pch.h"

SoundManagerC* SoundManagerC::sInstance = NULL;

SoundManagerC *SoundManagerC::CreateInstance()
{
	if (sInstance != NULL)return sInstance;
	else

		sInstance = new SoundManagerC();
	return sInstance;
}

void SoundManagerC::update()
{
	m_pSystem->update();
}

void SoundManagerC::reset()
{
	releaseSound(bgm);
	createSound(&bgm, "./Sounds/bgm_easy.mp3");
	releaseSound(bgm2);
	createSound(&bgm2, "./Sounds/otis.mp3");
	releaseSound(bgm3);
	createSound(&bgm3, "./Sounds/bgm_hyper.mp3");
}

void SoundManagerC::shutdown()
{
	releaseSound(bgm);
	releaseSound(select);
	releaseSound(bgm2);
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
	createSound(&bgm, "./Sounds/bgm_easy.mp3");
	createSound(&bgm2, "./Sounds/otis.mp3");
	createSound(&bgm3, "./Sounds/bgm_hyper.mp3");
	createSound(&select, "./Sounds/hit.wav");
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

void SoundManagerC::playBGM2()
{
	playSound(bgm2, true);
}

void SoundManagerC::playBGM3()
{
	playSound(bgm3, true);
}

void SoundManagerC::playSelectSFX()
{
	playSound(select, false);
}