#define SMALL_BUFFER 8
#define MEDIUM_BUFFER 32
#define LARGE_BUFFER 64

class UIManagerC
{
public:
	static UIManagerC	*CreateInstance();
	static UIManagerC	*GetInstance() { return sInstance; };
	~UIManagerC() {};

	void init();
	void update(DWORD milliseconds);
	void renderLogo();
	void renderScore();
	void renderGameOver();
	void UIManagerC::OGL_Render();
	void reset();

private:
	static UIManagerC *sInstance;
	UIManagerC() {};

	char8_t title[SMALL_BUFFER];
	char8_t startPrompt[MEDIUM_BUFFER];
	char8_t gameOverText[MEDIUM_BUFFER];
	char8_t restartPrompt[MEDIUM_BUFFER];

	DWORD totalTime;
	DWORD mCurrentTime;
	DWORD mLastUpdateTime;

};
