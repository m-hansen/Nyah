class SpriteManagerC
{
public:
	static SpriteManagerC	*CreateInstance();
	static SpriteManagerC	*GetInstance() {return sInstance;};
	~SpriteManagerC(){};

	void init();
	void renderBackground();
	void renderBullet(BulletColor color, int32_t animationFrameNo, GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat radius);

private:
	static SpriteManagerC *sInstance;
	SpriteManagerC(){};

	GLuint mBulletSpriteTexture;
	GLuint mBackgroundTexture;
	GLuint mPlayerSpriteTexture;
};