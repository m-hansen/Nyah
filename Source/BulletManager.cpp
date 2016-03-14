#include "pch.h"

BulletManagerC* BulletManagerC::sInstance = NULL;

BulletManagerC *BulletManagerC::CreateInstance()
{
	if (sInstance != NULL) { return sInstance; }
	else { sInstance = new BulletManagerC(); }
	return sInstance;
}

BulletManagerC::BulletManagerC() :
	mBulletWaves(), mWaveMap(), mPatternMap(), mWaveQueue()
{}

void BulletManagerC::init()
{
#pragma region Create Wave Types

	static WaveBuilderC waveBuilder;
	uint32_t start = static_cast<uint32_t>(RING_00_DEG);
	uint32_t end = static_cast<uint32_t>(RING_270_DEG);
	float_t counter = 0.0f;
	for (uint32_t i = start; i <= end; i++)
	{
		float angle = (counter * 90.0f) * RADIANS;
		counter += 1.0f;
		mWaveMap.Insert(WavePairType(static_cast<BulletWaveType>(i), waveBuilder(angle, PI / 2.0f, BulletWaveC::sNumBulletsRing)));
	}

	start = static_cast<uint32_t>(CRES_0_DEG);
	end = static_cast<uint32_t>(CRES_330_DEG);
	counter = 0.0f;
	for (uint32_t i = start; i <= end; ++i)
	{
		float angle = (counter * 30.0f) * RADIANS;
		counter += 1.0f;
		mWaveMap.Insert(WavePairType(static_cast<BulletWaveType>(i), waveBuilder(angle, PI, BulletWaveC::sNumBulletsCrescent)));
	}

	mWaveMap.Insert(WavePairType(SPIRAL_CLOCK, waveBuilder(true)));
	mWaveMap.Insert(WavePairType(SPIRAL_CNT_CLOCK, waveBuilder(false)));

#pragma endregion
	
	switch (CGame::GetMode())
	{
		case DifficultyMode::EASY: initEasy(); break;
		case DifficultyMode::MEDIUM: initMedium(); break;
		case DifficultyMode::HARD: initHard(); break;
	}

	mVelocity = CGame::GetPresets().velocity;
	mWaiting = true;
}

void BulletManagerC::initEasy()
{
#pragma region Create Patterns

	mPatternMap.Insert(PatternPairType(SINGLE_RING_1, WavePatternC({
		RING_00_DEG
	}, WavePatternC::sTimeBetweenRingsEasy)));

	mPatternMap.Insert(PatternPairType(SINGLE_RING_2, WavePatternC({
		RING_90_DEG
	}, WavePatternC::sTimeBetweenRingsEasy)));

	mPatternMap.Insert(PatternPairType(SINGLE_RING_3, WavePatternC({
		RING_180_DEG
	}, WavePatternC::sTimeBetweenRingsEasy)));

	mPatternMap.Insert(PatternPairType(SINGLE_RING_4, WavePatternC({
		RING_270_DEG
	}, WavePatternC::sTimeBetweenRingsEasy)));

	mPatternMap.Insert(PatternPairType(ALTERNATOR_EASY_1, WavePatternC({
		RING_00_DEG, RING_90_DEG, RING_00_DEG
	}, WavePatternC::sTimeBetweenSpecialEasy)));

	mPatternMap.Insert(PatternPairType(ALTERNATOR_EASY_2, WavePatternC({
		RING_90_DEG, RING_270_DEG, RING_90_DEG
	}, WavePatternC::sTimeBetweenSpecialEasy)));

	mPatternMap.Insert(PatternPairType(SEQUENTIAL_EASY_1, WavePatternC({
		RING_00_DEG, RING_90_DEG, RING_180_DEG
	}, WavePatternC::sTimeBetweenSpecialEasy)));

	mPatternMap.Insert(PatternPairType(SEQUENTIAL_EASY_2, WavePatternC({
		RING_180_DEG, RING_90_DEG, RING_00_DEG
	}, WavePatternC::sTimeBetweenSpecialEasy)));

#pragma endregion
}

void BulletManagerC::initMedium()
{
#pragma region Create Patterns

	mPatternMap.Insert(PatternPairType(ALTERNATOR_MEDIUM_1, WavePatternC({
		RING_00_DEG, RING_90_DEG, RING_00_DEG, RING_90_DEG
	}, WavePatternC::sTimeBetweenRingsMedium)));

	mPatternMap.Insert(PatternPairType(ALTERNATOR_MEDIUM_2, WavePatternC({
		RING_90_DEG, RING_270_DEG, RING_90_DEG, RING_270_DEG
	}, WavePatternC::sTimeBetweenRingsMedium)));

	mPatternMap.Insert(PatternPairType(SEQUENTIAL_MEDIUM_1, WavePatternC({
		RING_00_DEG, RING_90_DEG, RING_180_DEG, RING_270_DEG
	}, WavePatternC::sTimeBetweenRingsMedium)));

	mPatternMap.Insert(PatternPairType(SEQUENTIAL_MEDIUM_2, WavePatternC({
		RING_270_DEG, RING_180_DEG, RING_90_DEG, RING_00_DEG
	}, WavePatternC::sTimeBetweenRingsMedium)));

	mPatternMap.Insert(PatternPairType(FLIP_MEDIUM_1, WavePatternC({
		RING_00_DEG, RING_180_DEG
	}, WavePatternC::sTimeBetweenRingsMedium)));

	mPatternMap.Insert(PatternPairType(FLIP_MEDIUM_2, WavePatternC({
		RING_90_DEG, RING_270_DEG
	}, WavePatternC::sTimeBetweenRingsMedium)));

	mPatternMap.Insert(PatternPairType(SPIRAL_MEDIUM_1, WavePatternC({
		SPIRAL_CLOCK
	}, WavePatternC::sTimeBetweenSpiralsMedium)));

	mPatternMap.Insert(PatternPairType(SPIRAL_MEDIUM_2, WavePatternC({
		SPIRAL_CNT_CLOCK
	}, WavePatternC::sTimeBetweenSpiralsMedium)));

#pragma endregion
}

void BulletManagerC::initHard()
{
#pragma region Create Patterns

	mPatternMap.Insert(PatternPairType(ALTERNATOR_HARD_1, WavePatternC({
		RING_00_DEG, RING_90_DEG, RING_00_DEG, RING_90_DEG, RING_00_DEG
	}, WavePatternC::sTimeBetweenRingsHard)));

	mPatternMap.Insert(PatternPairType(ALTERNATOR_HARD_2, WavePatternC({
		RING_90_DEG, RING_270_DEG, RING_90_DEG, RING_270_DEG, RING_90_DEG
	}, WavePatternC::sTimeBetweenRingsHard)));

	mPatternMap.Insert(PatternPairType(SEQUENTIAL_HARD_1, WavePatternC({
		RING_00_DEG, RING_90_DEG, RING_180_DEG, RING_270_DEG, RING_00_DEG
	}, WavePatternC::sTimeBetweenRingsHard)));

	mPatternMap.Insert(PatternPairType(SEQUENTIAL_HARD_2, WavePatternC({
		RING_00_DEG, RING_270_DEG, RING_180_DEG, RING_90_DEG, RING_00_DEG
	}, WavePatternC::sTimeBetweenRingsHard)));

	mPatternMap.Insert(PatternPairType(FLIP_HARD_1, WavePatternC({
		RING_00_DEG, RING_180_DEG, RING_00_DEG, RING_180_DEG
	}, WavePatternC::sTimeBetweenFlipsHard)));

	mPatternMap.Insert(PatternPairType(FLIP_HARD_2, WavePatternC({
		RING_90_DEG, RING_270_DEG, RING_90_DEG, RING_270_DEG
	}, WavePatternC::sTimeBetweenFlipsHard)));

	mPatternMap.Insert(PatternPairType(SPIRAL_HARD_1, WavePatternC({
		SPIRAL_CLOCK, SPIRAL_CNT_CLOCK
	}, WavePatternC::sTimeBetweenSpiralsHard)));

	mPatternMap.Insert(PatternPairType(SPIRAL_HARD_2, WavePatternC({
		SPIRAL_CNT_CLOCK, SPIRAL_CLOCK
	}, WavePatternC::sTimeBetweenSpiralsHard)));

	mPatternMap.Insert(PatternPairType(FLURRY_HARD_1, WavePatternC({
		CRES_0_DEG, CRES_180_DEG, CRES_0_DEG, CRES_60_DEG,
		CRES_150_DEG, CRES_180_DEG, CRES_0_DEG, CRES_90_DEG,
		CRES_180_DEG, CRES_90_DEG, CRES_180_DEG, CRES_0_DEG,
		CRES_90_DEG, CRES_150_DEG, CRES_0_DEG, CRES_90_DEG
	}, WavePatternC::sTimeBetweenCrescentsHard)));

#pragma endregion
}

void BulletManagerC::LoadPattern()
{
	int32_t result;
	PatternType patternType;

	result = getRangedRandom(CGame::GetPresets().start, CGame::GetPresets().end);
	patternType = static_cast<PatternType>(result);
	WavePatternC& pattern = mPatternMap[patternType];

	for (auto& wave : pattern.GetWaveTypes())
	{
		mWaveQueue.Push(wave);
	}

	mCurrentWavePattern = pattern;
}

void BulletManagerC::SpawnWave()
{
	if (!mWaveQueue.IsEmpty())
	{
		mBulletWaves.PushBack(mWaveMap[mWaveQueue.Top()]);
		mWaveQueue.Pop();
	}
}

void BulletManagerC::shutdown()
{

}

void BulletManagerC::reset()
{
	delete sInstance;
	sInstance = NULL;
}

void BulletManagerC::renderSprites()
{
	for (auto& bulletWave : mBulletWaves)
	{
		bulletWave.render();
	}
}

SList<BulletWaveC>& BulletManagerC::getBulletWaves()
{
	return mBulletWaves;
}

void BulletManagerC::updateBullets(DWORD milliseconds)
{
	if (PhaseManagerC::GetInstance()->getPhase() == Phase::NYAH_ONE ||
		PhaseManagerC::GetInstance()->getPhase() == Phase::INVALID_PHASE)
		return;
	
	mCurrentTime += milliseconds;

	if (mWaiting)
	{
		if (mCurrentTime - mLastPatternUpdateTime > CGame::GetPresets().waitTime)
		{
			mLastPatternUpdateTime = mCurrentTime;
			mWaiting = false;
			LoadPattern();
			mLastSpawnTime = mCurrentTime;
			SpawnWave();
		}
	}
	else
	{
		if (mCurrentTime - mLastSpawnTime > mCurrentWavePattern.GetWaveTime())
		{
			if (mWaveQueue.IsEmpty() && !mWaiting)
			{
				mWaiting = true;
				mLastPatternUpdateTime = mCurrentTime;
			}
			if (!mWaiting)
			{
				mLastSpawnTime = mCurrentTime;
				SpawnWave();
			}
		}
	}

	for (auto& bulletWave : mBulletWaves)
	{
		bulletWave.update(milliseconds, mVelocity);
	}

	if (!mBulletWaves.IsEmpty())
	{
		if (mBulletWaves.Front().getWaveAtCenter())
		{
			mBulletWaves.PopFront();
		}
	}
}