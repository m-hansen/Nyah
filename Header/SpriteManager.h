class SpriteManagerC
{
public:
	static SpriteManagerC	*CreateInstance();
	static SpriteManagerC	*GetInstance() {return sInstance;};
	~SpriteManagerC(){};

	void init();
	void renderBackground();
	void renderBullet(GLint animationFrameNo, GLfloat left, GLfloat right, GLfloat top, GLfloat bottom);

private:
	static SpriteManagerC *sInstance;
	SpriteManagerC(){};

	GLuint mBulletSpriteTexture;
	GLuint mBackgroundTexture;
	GLuint mPlayerSpriteTexture;
};