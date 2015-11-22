class BulletManagerC
{
public:
	static BulletManagerC	*CreateInstance();
	static BulletManagerC	*GetInstance() { return sInstance; };
	~BulletManagerC() {};

	void	init();
	void	spawnWave();
	void	updateBullets(DWORD milliseconds);
	void	renderSprites();
	void	shutdown();

private:
	static BulletManagerC *sInstance;
	BulletManagerC() {};

	BulletC **bulletPtrs;
	static const int32_t NUM_BULLETS = 48;
};