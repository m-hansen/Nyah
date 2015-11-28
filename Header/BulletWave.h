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
	static const int32_t VELOCITY = -25;
	static const int32_t NUM_BULLETS = 48;
	static const int32_t BULLET_RADIUS = 135;
};
#define PI 3.1415926536
#define RADIANS (PI/180.0);