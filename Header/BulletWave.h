class BulletWaveC
{
public:
	BulletWaveC();
	~BulletWaveC();
	void update(DWORD milliseconds, float_t velocity);
	void render();
	bool8_t getWaveAtCenter();

	void AddBullet(BulletC bullet);
	SList<BulletC>& getBullets();

	static const int32_t sNumBulletsRing = 48;
	static const int32_t sNumBulletsCrescent = 32;
	static const int32_t sNumBulletsSpiral = 144;
	static const int32_t sBulletRadius = 145;
private:
	SList<BulletC> mBullets;
	bool8_t mWaveAtCenter;
};

class WaveBuilderC
{
public:
	BulletWaveC operator()(float_t gapAngle, float_t gapSize, int32_t numBullets);
	BulletWaveC operator()(bool clockwise);
};


#define PI 3.1415926536
#define RADIANS (PI/180.0);
#define INITIAL_WAVE_RADIUS 3000.0f