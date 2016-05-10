#include "pch.h"

// Declarations
const char8_t CGame::mGameTitle[]="Nyah";
CGame* CGame::sInstance=NULL;
DifficultyMode CGame::mMode;
HashMap<DifficultyMode, DifficultyPresets> CGame::presets;

void CGame::initDifficultyPresets()
{
	DifficultyPresets easy;
	easy.velocity = sVelocityEasy;
	easy.start = static_cast<int>(EASY_BEGIN) + 1;
	easy.end = static_cast<int>(EASY_END);
	easy.rotSpeed = sRotSpeedEasy;
	easy.waitTime = sWaitTimeEasy;
	presets.Insert(std::pair<DifficultyMode, DifficultyPresets>(DifficultyMode::EASY, easy));

	DifficultyPresets medium;
	medium.velocity = sVelocityMedium;
	medium.start = static_cast<int>(MEDIUM_BEGIN) + 1;
	medium.end = static_cast<int>(MEDIUM_END);
	medium.rotSpeed = sRotSpeedMedium;
	medium.waitTime = sWaitTimeMedium;
	presets.Insert(std::pair<DifficultyMode, DifficultyPresets>(DifficultyMode::MEDIUM, medium));

	DifficultyPresets hard;
	hard.velocity = sVelocityHard;
	hard.start = static_cast<int>(HARD_BEGIN) + 1;
	hard.end = static_cast<int>(HARD_END);
	hard.rotSpeed = sRotSpeedHard;
	hard.waitTime = sWaitTimeHard;
	presets.Insert(std::pair<DifficultyMode, DifficultyPresets>(DifficultyMode::HARD, hard));
}

BOOL Initialize (GL_Window* window, Keys* keys)					// Any OpenGL Initialization Goes Here
{
	initOpenGLDrawing(window, keys, 0.0f, 0.0f, 0.0f);
	CGame::CreateInstance();
	CGame::GetInstance()->init();
	return TRUE;						
}

void CGame::init()
{
	initDifficultyPresets();
	CGame::SetMode(DifficultyMode::EASY);

	StateManagerC::CreateInstance();
	InputManagerC::CreateInstance();
	SpriteManagerC::CreateInstance();
	BulletManagerC::CreateInstance();
	PhaseManagerC::CreateInstance();
	UIManagerC::CreateInstance();
	SoundManagerC::CreateInstance();
	PlayerC::CreateInstance();
	CollisionHandlerC::CreateInstance();
	GameTimeC::CreateInstance();
	HighScoresC::CreateInstance();
	
	HighScoresC::GetInstance()->init();
	GameTimeC::GetInstance()->reset();
	InputManagerC::GetInstance()->init();
	BulletManagerC::GetInstance()->init();
	StateManagerC::GetInstance()->setState(StateManagerC::TITLE);
	SpriteManagerC::GetInstance()->init();
	PhaseManagerC::GetInstance()->init();
	UIManagerC::GetInstance()->init();
	SoundManagerC::GetInstance()->init();
	PlayerC::GetInstance()->init();
}

void CGame::reset()
{
	BulletManagerC::GetInstance()->shutdown();
	BulletManagerC::GetInstance()->reset();
	BulletManagerC::CreateInstance();
	BulletManagerC::GetInstance()->init();

	PlayerC::GetInstance()->init();
	PhaseManagerC::GetInstance()->init();

	SoundManagerC::GetInstance()->reset();
	//UIManagerC::GetInstance()->reset();
	GameTimeC::GetInstance()->reset();

	StateManagerC::GetInstance()->setState(StateManagerC::PLAYING);

	// Start timers and music
	GameTimeC::GetInstance()->start();
	switch (CGame::GetMode())
	{
	case DifficultyMode::EASY: SoundManagerC::GetInstance()->playBGM(); break;
	case DifficultyMode::MEDIUM: SoundManagerC::GetInstance()->playBGM3(); break;
	case DifficultyMode::HARD: SoundManagerC::GetInstance()->playBGM2(); break;
	}
	
}

void CGame::UpdateFrame(DWORD milliseconds)			
{
	// Update frame, regardless of state
	SoundManagerC::GetInstance()->update();
	SpriteManagerC::GetInstance()->update(milliseconds);
	if (InputManagerC::GetInstance()->QuitPressed())
	{
		InputManagerC::GetInstance()->QuitGame();
	}
	
	switch (StateManagerC::GetInstance()->getState())
	{
		case StateManagerC::TITLE:
			if (InputManagerC::GetInstance()->GetStartButton())
			{
				CGame::GetInstance()->reset();
				SoundManagerC::GetInstance()->playSelectSFX();
			}
			if (InputManagerC::GetInstance()->GetDifficultyButton())
			{
				uint32_t modeNum = static_cast<uint32_t>(CGame::GetMode()) + 1;
				if (modeNum > 2)
					modeNum = 0;
				CGame::SetMode(static_cast<DifficultyMode>(modeNum));
				SoundManagerC::GetInstance()->playSelectSFX();
			}
			break;
		case StateManagerC::PLAYING:
			GameTimeC::GetInstance()->update(milliseconds);
			BulletManagerC::GetInstance()->updateBullets(milliseconds);
			PlayerC::GetInstance()->update(milliseconds);
			PhaseManagerC::GetInstance()->update(milliseconds);
			if (InputManagerC::GetInstance()->DebugPlayerKill())
			{
				StateManagerC::GetInstance()->setState(StateManagerC::GAMEOVER);
			}
			break;
		case StateManagerC::GAMEOVER:
			if (InputManagerC::GetInstance()->GetResetButton())
			{
				SoundManagerC::GetInstance()->playSelectSFX();
				CGame::GetInstance()->reset();
			}
			if (InputManagerC::GetInstance()->GetDifficultyButton())
			{
				SoundManagerC::GetInstance()->playSelectSFX();
				SoundManagerC::GetInstance()->reset();
				StateManagerC::GetInstance()->setState(StateManagerC::TITLE);
			}
			break;
	}
	
}

void CGame::DrawScene(void)											
{
	startOpenGLDrawing();

	// Render, regardless of state
	SpriteManagerC::GetInstance()->renderBackground();

	UIManagerC* uiManagerInstance = UIManagerC::GetInstance();
	
	switch (StateManagerC::GetInstance()->getState())
	{
		case StateManagerC::TITLE:
			uiManagerInstance->renderLogo();
			break;
		case StateManagerC::PLAYING:
			BulletManagerC::GetInstance()->renderSprites();
			PlayerC::GetInstance()->render();
			uiManagerInstance->renderScore();
			break;
		case StateManagerC::GAMEOVER:
			uiManagerInstance->renderGameOver();
			uiManagerInstance->renderScore();
			uiManagerInstance->renderHighScores();
			break;
	}
}

CGame *CGame::CreateInstance()
{
	sInstance = new CGame();
	return sInstance;
}

void CGame::shutdown()
{
	StateManagerC::GetInstance()->shutdown();
	BulletManagerC::GetInstance()->shutdown();
	SoundManagerC::GetInstance()->shutdown();
}

void CGame::DestroyGame(void)
{
	delete StateManagerC::GetInstance();	
	delete SpriteManagerC::GetInstance();
	delete BulletManagerC::GetInstance();
	delete PlayerC::GetInstance();
	delete InputManagerC::GetInstance();
	delete SoundManagerC::GetInstance();
	delete PhaseManagerC::GetInstance();
	delete HighScoresC::GetInstance();
	delete UIManagerC::GetInstance();
	delete GameTimeC::GetInstance();
	delete CollisionHandlerC::GetInstance();
	delete CGame::GetInstance();
}