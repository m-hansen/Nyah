class SpriteManagerC
{
public:
	static SpriteManagerC	*CreateInstance();
	static SpriteManagerC	*GetInstance() {return sInstance;};
	~SpriteManagerC(){};

	void init();
	void renderBackground();
	void renderBullet();
	void updateSprites(DWORD milliseconds);

private:
	static SpriteManagerC *sInstance;
	SpriteManagerC(){};

	GLuint mBulletSpriteTexture;
	GLuint mBackgroundTexture;
	GLuint mPlayerSpriteTexture;

	DWORD mLastUpdateTime;
	DWORD mCurrentTime;
};

#define MOOD_UPDATE_DELTA_TIME 100