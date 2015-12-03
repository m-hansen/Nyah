class SpriteManagerC
{
public:
	static SpriteManagerC	*CreateInstance();
	static SpriteManagerC	*GetInstance() {return sInstance;};
	~SpriteManagerC(){};

	void init();
	void update(DWORD milliseconds);
	void renderBackground();
	void renderBullet(BulletAnimationState state, BulletColor color, int32_t animationFrameNo, GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat radius);
	void renderPlayer(int32_t animationFrameNo, GLfloat left, GLfloat right, GLfloat top, GLfloat bottom);
	void SpriteManagerC::OGL_Render(struct RenderData img, GLuint textureID);
	void SpriteManagerC::OGL_Render2(struct RenderData img, GLuint textureID);

private:
	static SpriteManagerC *sInstance;
	SpriteManagerC(){};

	// Private functions
	GLuint loadTexture(char8_t* fileToLoad);

	// Private variables
	GLuint mBulletSpriteTexture;
	GLuint mBackgroundTexture;
	GLuint mPlayerSpriteTexture;
	GLuint colorStep;
	GLuint colorDelta;

	GLfloat angle;
	GLint rotationDirection;

	DWORD mCurrentTime;
	DWORD mLastColorUpdateTime;
	DWORD mLastAngleUpdateTime;
};
#define COLOR_UPDATE_DELTA_TIME 100
#define ANGLE_UPDATE_DELTA_TIME 1
#define ROT_SPEED_SLOW 0.5f
#define ROT_SPEED_MEDIUM 1.0f
#define ROT_SPEED_FAST 1.5f