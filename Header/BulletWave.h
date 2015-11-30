struct BulletList
{
	BulletC* bulletPtr;
	struct BulletList *nextBullet;
};
typedef struct BulletList BulletListT;

class BulletWaveC
{
public:
	BulletWaveC(int32_t VELOCITY);
	~BulletWaveC();
	void update(DWORD milliseconds);
	void render();
	bool8_t getWaveAtCenter();
private:
	BulletListT *topOfBulletList;
	bool8_t waveAtCenter;
	static const int32_t NUM_BULLETS = 48;
	static const int32_t BULLET_RADIUS = 135;
};
#define PI 3.1415926536
#define RADIANS (PI/180.0);