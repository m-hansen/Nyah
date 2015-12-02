class BulletC : public ObjectC
{
public:
	BulletC();
	BulletC(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY, float_t radius, BulletColor color, float_t theta);
	~BulletC();
	void update(DWORD milliseconds);
	virtual void render();
	void doCollisions();
	void move(DWORD milliseconds);
	void updateAnimationFrame(DWORD milliseconds);
	CollisionRectangle* getCollisionRectangle();
	bool8_t getIsAtCenter();
private:

	bool8_t mEnabled;
	float_t mRadius;
	float_t mTheta;
	int32_t animationFrameNo;
	bool8_t mAtRest;
	bool8_t isAtCenter;
	BulletColor mColor;
	BulletAnimationState animState;
	CollisionRectangle mCollRect;

	DWORD mLastUpdateTime;
	DWORD mCurrentTime;
};
#define ANIMATION_FRAME_UPDATE_DELTA_TIME 100
#define THRESHOLD 10.0