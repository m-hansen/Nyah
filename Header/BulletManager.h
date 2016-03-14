class BulletWaveC;

//using namespace Library;

class BulletManagerC
{
public:
	static BulletManagerC	*CreateInstance();
	static BulletManagerC	*GetInstance() { return sInstance; };
	~BulletManagerC() {};

	void	init();
	void	initEasy();
	void	initMedium();
	void	initHard();
	void	LoadPattern();
	void	SpawnWave();
	void	updateBullets(DWORD milliseconds);
	void	renderSprites();
	void	shutdown();
	void	reset();
	SList<BulletWaveC>& getBulletWaves();
	bool8_t getHasStartedSpawning() { return hasStartedSpawning; };

private:
	static BulletManagerC *sInstance;
	BulletManagerC();

	typedef std::pair<BulletWaveType, BulletWaveC> WavePairType;
	HashMap<BulletWaveType, BulletWaveC> mWaveMap;

	typedef std::pair<PatternType, WavePatternC> PatternPairType;
	HashMap<PatternType, WavePatternC> mPatternMap;

	Queue<BulletWaveType> mWaveQueue;

	WavePatternC mCurrentWavePattern;

	SList<BulletWaveC> mBulletWaves;

	float_t mVelocity;

	bool8_t hasStartedSpawning;
	bool8_t mWaiting;

	DWORD mLastSpawnTime;
	DWORD mLastPatternUpdateTime;
	DWORD mCurrentTime;
};
#define INCREASE_SPAWN_SPEED_DELTA_TIME 3000
#define TIME_BETWEEN_PATTERNS_EASY 8000
#define TIME_BETWEEN_PATTERNS_HARD 2750
#define VELOCITY_HARD -100