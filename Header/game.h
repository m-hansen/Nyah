class CGame
{
public:
	const char8_t *GetGameTitle(){return mGameTitle;}
	static CGame	*CreateInstance();
	static CGame	*GetInstance() {return sInstance;};
	static DifficultyMode GetMode() { return mMode; };
	static void SetMode(static DifficultyMode mode) { mMode = mode; };
	static DifficultyPresets GetPresets() { return presets[mMode]; };

	~CGame() {};
	void DrawScene();
	void UpdateFrame(DWORD milliseconds);
	void DestroyGame();
	void init();
	void initDifficultyPresets();
	void reset();
	void shutdown();

	static const uint32_t mScreenWidth = 1024;
	static const uint32_t mScreenHeight = 768;
	static const uint32_t mBitsPerPixel = 32;
	
private:
	static HashMap<DifficultyMode, DifficultyPresets> presets;
	static DifficultyMode mMode;
	static const char8_t mGameTitle[20];
	static CGame *sInstance;
	CGame(){};
};