class BulletC : public ObjectC
{
public:
	BulletC();
	BulletC(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY, float_t radius);
	~BulletC();
	void update(DWORD milliseconds);
	virtual void render();
	void doCollisions();
	void move();
	void updateAnimationFrame(DWORD milliseconds);
private:

	bool8_t mEnabled;
	float_t mRadius;
	int32_t animationFrameNo;
	bool8_t mAtRest;

	DWORD mLastUpdateTime;
	DWORD mCurrentTime;
};
#define ANIMATION_FRAME_UPDATE_DELTA_TIME 100