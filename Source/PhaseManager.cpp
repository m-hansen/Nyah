#include <Windows.h>
#include "baseTypes.h"
#include "GameTime.h"
#include "PhaseManager.h"
#include "SoundManager.h"

PhaseManagerC* PhaseManagerC::sInstance = NULL;

PhaseManagerC* PhaseManagerC::CreateInstance()
{
	if (sInstance != NULL) { return sInstance; }
	else { sInstance = new PhaseManagerC(); }
	return sInstance;
}

void PhaseManagerC::init()
{
	mCurrentTime = 0;
	mPhase = INVALID_PHASE;
}

void PhaseManagerC::update(DWORD milliseconds)
{
	mCurrentTime = GameTimeC::GetInstance()->getCurrentTimeInSeconds();
	if (mCurrentTime >= PHASE_SEVEN_BEGIN)
	{
		mPhase = NYAH_SEVEN;
	}
	else if (mCurrentTime >= PHASE_SIX_BEGIN)
	{
		mPhase = NYAH_SIX;
		SoundManagerC::GetInstance()->playBGM2();
	}
	else if (mCurrentTime >= PHASE_FIVE_BEGIN)
	{
		mPhase = NYAH_FIVE;
	}
	else if (mCurrentTime >= PHASE_FOUR_BEGIN)
	{
		mPhase = NYAH_FOUR;
	}
	else if (mCurrentTime >= PHASE_THREE_BEGIN)
	{
		mPhase = NYAH_THREE;
	}
	else if (mCurrentTime >= PHASE_TWO_BEGIN)
	{
		mPhase = NYAH_TWO;
	}
	else if (mCurrentTime >= PHASE_ONE_BEGIN)
	{
		mPhase = NYAH_ONE;
	}
	else
	{
		mPhase = INVALID_PHASE;
	}
}

Phase PhaseManagerC::getPhase()
{
	return mPhase;
}

void PhaseManagerC::getPhaseAsString(char8_t* phaseAsString)
{
	switch (mPhase)
	{
		case NYAH_ONE:
			strcpy(phaseAsString, "Phase1");
			break;
		case NYAH_TWO:
			strcpy(phaseAsString, "Phase2");
			break;
		case NYAH_THREE:
			strcpy(phaseAsString, "Phase3");
			break;
		case NYAH_FOUR:
			strcpy(phaseAsString, "Phase4");
			break;
		case NYAH_FIVE:
			strcpy(phaseAsString, "Phase5");
			break;
		default:
			strcpy(phaseAsString, "UNRECOGNIZED PHASE");
	}
}