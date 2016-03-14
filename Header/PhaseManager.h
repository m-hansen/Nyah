class GameTimeC;

class PhaseManagerC
{
public:
	

	static PhaseManagerC* CreateInstance();
	static PhaseManagerC* GetInstance() { return sInstance; };
	~PhaseManagerC() {};

	void init();
	void destroy();
	void update(DWORD milliseconds);
	Phase getPhase();
	void getPhaseAsString(char8_t* phaseAsString);
private:
	static PhaseManagerC* sInstance;
	PhaseManagerC() {};

	Phase mPhase;
	GameTimeC* mGameTimer;
	DWORD mCurrentTime;
};
#define PHASE_ONE_BEGIN 0
#define PHASE_TWO_BEGIN 2
#define PHASE_THREE_BEGIN 10
#define PHASE_FOUR_BEGIN 26
#define PHASE_FIVE_BEGIN 44

//0 8 24 42 60 63 69