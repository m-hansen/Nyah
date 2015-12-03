class GameTimeC
{
public:
	static GameTimeC *CreateInstance();
	static GameTimeC *GetInstance() { return sInstance; };
	~GameTimeC() {};
	void reset();
	void pause();
	void start();
	void update(DWORD milliseconds);
	DWORD getCurrentTime();
	DWORD getCurrentTimeInSeconds();
private:
	static GameTimeC *sInstance;
	GameTimeC() {};

	DWORD mCurrentTime;
	bool8_t mIsRunning;
};