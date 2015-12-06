#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl/gl.h>												// Header File For The OpenGL32 Library
#include <gl/glu.h>												// Header File For The GLu32 Library
#include <gl/glut.h>
#include <assert.h>
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "PhaseManager.h"
#include "GameTime.h"
#include "random.h"
#include "soil.h"
#include "HighScores.h"
#include "UIManager.h"

UIManagerC* UIManagerC::sInstance = NULL;

UIManagerC *UIManagerC::CreateInstance()
{
	if (sInstance != NULL) { return sInstance; }
	else { sInstance = new UIManagerC(); }
	return sInstance;
}

void UIManagerC::init()
{
	strcpy(title, "NYAH");
	strcpy(startPrompt, "PRESS SPACE TO PLAY");
	strcpy(gameOverText, "Game Over");
	strcpy(restartPrompt, "Press ENTER to restart");
	mCachedPhaseManager = PhaseManagerC::GetInstance();
}

void UIManagerC::renderScore()
{
	char8_t timerString[LARGE_BUFFER];
	formatTime(GameTimeC::GetInstance()->getCurrentTime(), timerString);

	int32_t lengthOfString = (int32_t)strlen(timerString);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	// Timer
	glPushMatrix();
	glScalef(1.0f, 1.0f, 1.0f);
	glTranslatef(-(lengthOfString * 52), 1800.0f, 0.0f);
	for (int32_t i = 0; i < lengthOfString; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, timerString[i]);
	}
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void UIManagerC::renderLogo()
{
	int32_t lengthOfString = (int32_t)strlen(title);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	// Title
	glPushMatrix();
	glScalef(4.0f, 4.0f, 4.0f);
	glTranslatef(-(lengthOfString * 52), 100.0f, 0.0f);
	for (int32_t i = 0; i < lengthOfString; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, title[i]);
	}
	glPopMatrix();

	// Start prompt
	glPushMatrix();
	lengthOfString = (int32_t)strlen(startPrompt);
	glTranslatef(-(lengthOfString * 52), -500.0f, 0.0f);
	for (int32_t i = 0; i < lengthOfString; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, startPrompt[i]);
	}
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void UIManagerC::renderGameOver()
{
	int32_t lengthOfString = (int32_t)strlen(gameOverText);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	// Game over text
	glPushMatrix();
	glScalef(4.0f, 4.0f, 4.0f);

	glTranslatef(-(lengthOfString * 52), 200.0f, 0.0f);
	for (int32_t i = 0; i < lengthOfString; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, gameOverText[i]);
	}
	glPopMatrix();

	// Display high scores
	DWORD* scores = HighScoresC::GetInstance()->getHighScores();
	int32_t numScores = HighScoresC::GetInstance()->getMaxNumberOfHighScores();
	int32_t vertPadding = 140;
	for (int32_t i = 0; i < numScores; i++)
	{
		char floatBuffer[MEDIUM_BUFFER];
		formatTime(scores[i], floatBuffer);

		lengthOfString = (int32_t)strlen(floatBuffer);

		glPushMatrix();
		glScalef(1.0f, 1.0f, 1.0f);

		glTranslatef(-(lengthOfString * 52), 300.0f - (vertPadding * i), 0.0f);
		for (int32_t j = 0; j < lengthOfString; j++)
		{
			glColor3f(1.0f, 1.0f, 1.0f);
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, floatBuffer[j]);
		}
		glPopMatrix();
	}
	
	// Restart prompt
	glPushMatrix();
	lengthOfString = (int32_t)strlen(restartPrompt);
	glTranslatef(-(lengthOfString * 52), -1500.0f, 0.0f);
	for (int32_t i = 0; i < lengthOfString; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, restartPrompt[i]);
	}
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
}

void UIManagerC::renderPhaseText()
{
	char8_t phaseText[MEDIUM_BUFFER] = "";
	PhaseManagerC::GetInstance()->getPhaseAsString(phaseText);

	int32_t lengthOfString = (int32_t)strlen(phaseText);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glScalef(1.0f, 1.0f, 1.0f);
	glTranslatef(-(lengthOfString * 52), 0.0f, 0.0f);
	for (int32_t i = 0; i < lengthOfString; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, phaseText[i]);
	}
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void UIManagerC::formatTime(DWORD time, char8_t* formattedTime)
{
	char8_t minutesString[SMALL_BUFFER];
	char8_t secondsString[SMALL_BUFFER];
	char8_t millisString[SMALL_BUFFER];
	char8_t timerString[LARGE_BUFFER];
	memset(timerString, 0x00, strlen(timerString));

	int32_t millis = (time % 1000) / 10;
	int32_t seconds = (time / 1000) % 60;
	int32_t minutes = (time / 1000) / 60;
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

	strcpy(formattedTime, timerString);
}