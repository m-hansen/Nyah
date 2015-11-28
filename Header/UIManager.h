class UIManagerC
{
public:
	static UIManagerC	*CreateInstance();
	static UIManagerC	*GetInstance() { return sInstance; };
	~UIManagerC() {};

	void init();
	void renderLogo();
	void renderScore();
	void UIManagerC::OGL_Render();

private:
	static UIManagerC *sInstance;
	UIManagerC() {};

	char8_t title[8];
	char8_t startPrompt[32];
};
