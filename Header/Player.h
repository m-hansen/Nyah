class PlayerC : public ObjectC
{
public:
	static PlayerC *CreateInstance();
	static PlayerC *GetInstance() { return sInstance; };
	//PlayerC();
	//PlayerC(float initPosX, float initPosY, float initVelX, float initVelY);
	~PlayerC() {};
	void init();
	void update(DWORD milliseconds);
	virtual void render();
private:
	static PlayerC *sInstance;
	PlayerC() {};

	void move(DWORD milliseconds);

	float_t mRadius;
	float_t mAngle;
	Coord2D mOrigin;

	DWORD mLastUpdateTime;
	DWORD mCurrentTime;
};
#define ANGLE_INCREMENT 0.01f		// The speed the player rotates at
#define PLAYER_WIDTH 100			// Player width
#define PLAYER_HEIGHT 100			// Player height
#define INITIAL_RADIUS 200.0f		// The radius the player rotates around