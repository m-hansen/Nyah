#include "fmod.hpp"
#include "fmod_errors.h"

class SoundManagerC
{
public:
	static SoundManagerC	*CreateInstance();
	static SoundManagerC	*GetInstance() { return sInstance; };
	~SoundManagerC() {};

	void init();
	void reset();
	void createSound(FMOD::Sound** pSound, const char* pFile);
	void playSound(FMOD::Sound* pSound, bool bLoop);
	void releaseSound(FMOD::Sound* pSound);
	void playBGM();
	void playSelectSFX();
	void shutdown();

private:
	static SoundManagerC *sInstance;
	SoundManagerC() {};

	FMOD::System *m_pSystem;
	FMOD::Sound* bgm;
	FMOD::Sound* select;
};
