#define MAX_HIGH_SCORES 10
class HighScoresC
{
public:
	static HighScoresC* CreateInstance();
	static HighScoresC* GetInstance() { return sInstance; };
	~HighScoresC() {};
	void init();
	void loadHighScores();
	void storeHighScores();
	bool determineIfHighScore();
	void addNewHighScoreToTable(DWORD newScore, int32_t tableIndex);
	DWORD* getHighScores() { return mHighScores; };
	DWORD getMaxNumberOfHighScores() { return MAX_HIGH_SCORES; }
private:
	static HighScoresC* sInstance;
	HighScoresC() {};
	DWORD mHighScores[MAX_HIGH_SCORES];
};