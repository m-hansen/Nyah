#pragma once
struct DifficultyPresets{
	float_t velocity;
	int32_t start;
	int32_t end;
	float_t rotSpeed;
	DWORD waitTime;
};

enum class DifficultyMode
{
	EASY,
	MEDIUM,
	HARD
};

static const float_t sVelocityEasy = -1800.0f;
static const float_t sVelocityMedium = -2200.0f;
static const float_t sVelocityHard = -2800.0f;
static const float_t sRotSpeedEasy = 0.0f;;
static const float_t sRotSpeedMedium = 0.25f;
static const float_t sRotSpeedHard = 1.0f;
static const DWORD sWaitTimeEasy = 750;
static const DWORD sWaitTimeMedium = 550;
static const DWORD sWaitTimeHard = 350;