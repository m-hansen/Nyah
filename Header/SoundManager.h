

class SoundManagerC
{
public:
	static SoundManagerC	*CreateInstance();
	static SoundManagerC	*GetInstance() { return sInstance; };
	~SoundManagerC() {};

	void init();
	void reset();
	void update();
	void createSound(FMOD::Sound** pSound, const char* pFile);
	void playSound(FMOD::Sound* pSound, bool bLoop);
	void releaseSound(FMOD::Sound* pSound);
	void playBGM();
	void playBGM2();
	void playBGM3();
	void playSelectSFX();
	void shutdown();

private:
	static SoundManagerC *sInstance;
	SoundManagerC() {};

	FMOD::System *m_pSystem;
	FMOD::Sound* bgm;
	FMOD::Sound* bgm2;
	FMOD::Sound* bgm3;
	FMOD::Sound* select;
};
