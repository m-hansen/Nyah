class BulletWaveC;

struct BulletWaveList
{
	BulletWaveC* bulletWavePtr;
	struct BulletWaveList *nextBulletWave;
};
typedef struct BulletWaveList BulletWaveListT;

class BulletManagerC
{
public:
	static BulletManagerC	*CreateInstance();
	static BulletManagerC	*GetInstance() { return sInstance; };
	~BulletManagerC() {};

	void	init();
	void	spawnBulletWave();
	void	updateBullets(DWORD milliseconds);
	void	renderSprites();
	void	shutdown();
	void	reset();
	BulletWaveListT* getClosestBulletWave();
	bool8_t getHasStartedSpawning() { return hasStartedSpawning; };

private:
	static BulletManagerC *sInstance;
	BulletManagerC() {};

	BulletWaveListT *topOfBulletWaveList;
	static const int32_t MAX_NUM_WAVES = 7;
	int32_t TIME_BETWEEN_WAVES;
	int32_t TIME_BETWEEN_SPIRALS;
	int32_t TIME_BETWEEN_RINGS;
	int32_t VELOCITY;
	bool8_t hasStartedSpawning;

	DWORD mLastSpawnTime;
	DWORD mLastSpeedIncreaseTime;
	DWORD mCurrentTime;
};
#define INCREASE_SPAWN_SPEED_DELTA_TIME 3000