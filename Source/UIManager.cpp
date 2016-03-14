#include "pch.h"

UIManagerC* UIManagerC::sInstance = NULL;

UIManagerC *UIManagerC::CreateInstance()
{
	if (sInstance != NULL) { return sInstance; }
	else { sInstance = new UIManagerC(); }
	return sInstance;
}

void UIManagerC::init()
{
	title = "NYAH";
	startPrompt = "Press ENTER to Play";
	gameOver = "GAME OVER";
	restartPrompt = "Press ENTER to restart";
	difficultyPrompt = "Press SPACE to change difficulty";
	back = "Press SPACE to return to title screen";

	mCachedPhaseManager = PhaseManagerC::GetInstance();
}

void UIManagerC::renderScore()
{
	char8_t minutesString[SMALL_BUFFER];
	char8_t secondsString[SMALL_BUFFER];
	char8_t millisString[SMALL_BUFFER];
	char8_t timerString[LARGE_BUFFER];
	memset(timerString, 0x00, strlen(timerString));

	DWORD currentTime = GameTimeC::GetInstance()->getCurrentTime();
	int32_t millis = (currentTime % 1000) / 10;
	int32_t seconds = (currentTime / 1000) % 60;
	int32_t minutes = (currentTime / 1000) / 60;
	itoa(millis, millisString, 10);
	itoa(seconds, secondsString, 10);
	itoa(minutes, minutesString, 10);

	strcat(timerString, minutesString);
	strcat(timerString, ":");
	if (seconds < 10)
	{
		strcat(timerString, "0");
	}
	strcat(timerString, secondsString);
	strcat(timerString, ":");
	if (millis < 10)
	{
		strcat(timerString, "0");
	}
	strcat(timerString, millisString);

	int32_t lengthOfString = (int32_t)strlen(timerString);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	// Timer
	glPushMatrix();
	glScalef(1.0f, 1.0f, 1.0f);
	glTranslatef(-(lengthOfString * 52), 1800.0f, 0.0f);
	for (int i = 0; i < lengthOfString; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, timerString[i]);
	}
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void UIManagerC::renderLogo()
{
	switch (CGame::GetMode())
	{
		case DifficultyMode::EASY: difficulty = "NORMAL"; break;
		case DifficultyMode::MEDIUM: difficulty = "HYPER"; break;
		case DifficultyMode::HARD: difficulty = "NYAHHHH"; break;
	}

	int32_t lengthOfString = title.size();
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	// Title
	glPushMatrix();
	glScalef(4.0f, 4.0f, 4.0f);
	glTranslatef(-(lengthOfString * 52), 100.0f, 0.0f);
	for (int i = 0; i < lengthOfString; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, title[i]);
	}
	glPopMatrix();

	// Start prompt
	glPushMatrix();
	lengthOfString = startPrompt.size();
	glTranslatef(-(lengthOfString * 52), -500.0f, 0.0f);
	for (int i = 0; i < lengthOfString; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, startPrompt[i]);
	}
	glPopMatrix();

	// Difficulty Prompt
	glPushMatrix();
	lengthOfString = difficultyPrompt.size();
	glTranslatef(-(lengthOfString * 52), -1300.0f, 0.0f);
	for (int i = 0; i < lengthOfString; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, difficultyPrompt[i]);
	}
	glPopMatrix();

	// Difficulty Mode
	glPushMatrix();
	lengthOfString = difficulty.size();
	glTranslatef(-(lengthOfString * 52), -1600.0f, 0.0f);
	for (int i = 0; i < lengthOfString; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, difficulty[i]);
	}
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void UIManagerC::renderGameOver()
{
	int32_t lengthOfString = gameOver.size();
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	// Game over text
	glPushMatrix();
	glScalef(3.0f, 3.0f, 3.0f);
	glTranslatef(-(lengthOfString * 52), 100.0f, 0.0f);
	for (int i = 0; i < lengthOfString; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, gameOver[i]);
	}
	glPopMatrix();

	// Restart prompt
	glPushMatrix();
	lengthOfString = restartPrompt.size();
	glTranslatef(-(lengthOfString * 52), -500.0f, 0.0f);
	for (int i = 0; i < lengthOfString; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, restartPrompt[i]);
	}
	glPopMatrix();

	// Title Screen prompt
	glPushMatrix();
	lengthOfString = back.size();
	glTranslatef(-(lengthOfString * 52), -1100.0f, 0.0f);
	for (int i = 0; i < lengthOfString; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, back[i]);
	}
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
}

void UIManagerC::renderPhaseText()
{
	char phaseText[MEDIUM_BUFFER] = "";
	PhaseManagerC::GetInstance()->getPhaseAsString(phaseText);

	int32_t lengthOfString = (int32_t)strlen(phaseText);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glScalef(1.0f, 1.0f, 1.0f);
	glTranslatef(-(lengthOfString * 52), 0.0f, 0.0f);
	for (int i = 0; i < lengthOfString; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, phaseText[i]);
	}
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}