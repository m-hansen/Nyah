class BulletWaveC;
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

private:
	static BulletManagerC *sInstance;
	BulletManagerC() {};

	BulletWaveC **bulletWavePtrs;
	static const int32_t MAX_NUM_WAVES = 7;
	int32_t TIME_BETWEEN_WAVES;

	DWORD mLastSpawnTime;
	DWORD mLastSpeedIncreaseTime;
	DWORD mCurrentTime;
};
#define INCREASE_SPAWN_SPEED_DELTA_TIME 5000