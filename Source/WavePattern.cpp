#include "pch.h"

#pragma region Wave Pattern

WavePatternC::WavePatternC(std::initializer_list<BulletWaveType> waveTypes, int32_t time) :
	mWaveTypes(waveTypes.size()), mPatternTime(waveTypes.size() * time), mWaveTime(time)
{
	for (auto i : waveTypes)
	{
		mWaveTypes.PushBack(i);
	}
}

Vector<BulletWaveType>& WavePatternC::GetWaveTypes()
{
	return mWaveTypes;
}

int32_t WavePatternC::GetPatternTime()
{
	return mPatternTime;
}

int32_t WavePatternC::GetWaveTime()
{
	return mWaveTime;
}

#pragma endregion

