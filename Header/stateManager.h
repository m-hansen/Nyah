class StateManagerC
{
public:
	static StateManagerC	*CreateInstance();
	static StateManagerC	*GetInstance() {return sInstance;};
	~StateManagerC(){};
	enum 
	{
		INVALID,
		TITLE,
		PLAYING,
		GAMEOVER,
		PAUSED,
		MAX
	};
	int32_t		getState();
	void		setState(int32_t stateToSet);
	void		shutdown();
private:
	static StateManagerC *sInstance;
	StateManagerC(){};
	int32_t		mCurrentState;
};