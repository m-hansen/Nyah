#pragma once
class WavePatternC
{
public:
	WavePatternC() {};
	WavePatternC(std::initializer_list<BulletWaveType> waveTypes, int32_t time);
	Vector<BulletWaveType>& GetWaveTypes();
	int32_t GetPatternTime();
	int32_t GetWaveTime();
	static const int32_t sTimeBetweenSpecialEasy = 475;
	static const int32_t sTimeBetweenRingsEasy = 500;
	
	static const int32_t sTimeBetweenRingsMedium = 375;
	static const int32_t sTimeBetweenSpiralsMedium = 2800;

	static const int32_t sTimeBetweenRingsHard = 360;
	static const int32_t sTimeBetweenFlipsHard = 500;
	static const int32_t sTimeBetweenSpiralsHard = 2200;
	static const int32_t sTimeBetweenCrescentsHard = 340;
private:
	Vector<BulletWaveType> mWaveTypes;
	int32_t mPatternTime;
	int32_t mWaveTime;
};

