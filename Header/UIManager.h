#define SMALL_BUFFER 8
#define MEDIUM_BUFFER 32
#define LARGE_BUFFER 64

class PhaseManagerC;

class UIManagerC
{
public:
	static UIManagerC	*CreateInstance();
	static UIManagerC	*GetInstance() { return sInstance; };
	~UIManagerC() {};

	void init();
	void renderLogo();
	void renderScore();
	void renderGameOver();
	void renderPhaseText();

private:
	static UIManagerC *sInstance;
	UIManagerC() {};

	std::string title;
	std::string difficulty;
	std::string startPrompt;
	std::string difficultyPrompt;
	std::string restartPrompt;
	std::string gameOver;
	std::string back;

	PhaseManagerC* mCachedPhaseManager;
};
