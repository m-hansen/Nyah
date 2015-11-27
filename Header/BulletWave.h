class BulletWaveC
{
public:
	BulletWaveC();
	~BulletWaveC();
	void update(DWORD milliseconds);
	void render();
	bool8_t getWaveAtCenter();
private:
	BulletC **bulletPtrs;
	BulletC *firstBullet;
	uint32_t numBullets;
	bool8_t waveAtCenter;
	static const int32_t NUM_BULLETS = 48;
};
#define PI 3.1415926536