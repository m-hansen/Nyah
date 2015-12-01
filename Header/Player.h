class PlayerC : public ObjectC
{
public:
	static PlayerC *CreateInstance();
	static PlayerC *GetInstance() { return sInstance; };
	~PlayerC() {};
	void init();
	void update(DWORD milliseconds);
	void checkForCollision();
	virtual void render();
	CollisionRectangle* getCollisionRectangle();
private:
	static PlayerC *sInstance;
	PlayerC() {};

	void move(DWORD milliseconds);

	int32_t animationFrameNo;
	int32_t rotateAnimationDirection;
	float_t mRadius;
	float_t mAngle;
	Coord2D mOrigin;
	CollisionRectangle mCollRect;

	BulletManagerC* bulletManagerInstance;

	DWORD mLastUpdateTime;
	DWORD mCurrentTime;
};
#define ANGLE_INCREMENT 0.01f		// The speed the player rotates at
#define PLAYER_WIDTH 100			// Player width
#define PLAYER_HEIGHT 100			// Player height
#define INITIAL_RADIUS 250.0f		// The radius the player rotates around
#define ANIMATION_FRAME_UPDATE_DELTA_TIME 100	//how fast the player animation changes frames
#define FIRST_ANIM_FRAME 0
#define LAST_ANIM_FRAME 3