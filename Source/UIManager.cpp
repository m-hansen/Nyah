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
	strcpy_s(title, "NYAH");
	strcpy_s(startPrompt, "PRESS SPACE TO PLAY");
	strcpy_s(gameOverText, "Game Over");
	strcpy_s(restartPrompt, "Press ENTER to restart");
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
	for (int32_t i = 0; i < lengthOfString; ++i)
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
	for (int32_t i = 0; i < lengthOfString; ++i)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, title[i]);
	}
	glPopMatrix();

	// Start prompt
	glPushMatrix();
	lengthOfString = (int32_t)strlen(startPrompt);
	glTranslatef(-(lengthOfString * 52), -500.0f, 0.0f);
	for (int32_t i = 0; i < lengthOfString; ++i)
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
	glColor3f(1.0f, 1.0f, 1.0f);

	glTranslatef(-(lengthOfString * 52), 200.0f, 0.0f);
	for (int32_t i = 0; i < lengthOfString; ++i)
	{
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, gameOverText[i]);
	}
	glPopMatrix();
	
	// Restart prompt
	glPushMatrix();
	lengthOfString = (int32_t)strlen(restartPrompt);
	glTranslatef(-(lengthOfString * 52), -1500.0f, 0.0f);
	for (int32_t i = 0; i < lengthOfString; ++i)
	{
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, restartPrompt[i]);
	}
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
}

void UIManagerC::renderHighScores()
{
	const Coord2D HIGHSCORE_POSITION = { GLUT_WINDOW_WIDTH / 2, GLUT_WINDOW_HEIGHT / 2 };
	const Coord2D RANK_OFFSET = { -900, 0 };
	const Coord2D NAME_OFFSET = { -550, 0 };
	const Coord2D TIME_OFFSET = { 300, 0 };

	GLColor standardColor;
	standardColor.red = 1.0f;
	standardColor.green = 1.0f;
	standardColor.blue = 1.0f;

	GLColor highlightColor;
	highlightColor.red = 0.0f;
	highlightColor.green = 1.0f;
	highlightColor.blue = 1.0f;

	int32_t newHighScoreIndex = HighScoresC::GetInstance()->getNewHighScoreIndex();

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	int32_t lengthOfString = 0;

	// Display high scores
	HighScoreEntry* scores = HighScoresC::GetInstance()->getHighScores();
	int32_t numScores = HighScoresC::GetInstance()->getMaxNumberOfHighScores();
	int32_t vertPadding = 140;
	int32_t maxScoreStringLength = log10(numScores) + 1;
	for (int32_t i = 0; i < numScores; ++i)
	{
		char8_t scoreBuffer[MEDIUM_BUFFER];
		std::string name = scores[i].name;

		formatTime(scores[i].score, scoreBuffer);

		int32_t rank = i + 1;

		// Display ranking of high scores
		// Get the length of each integer
		int32_t lengthOfRankInteger = (rank == 0 ? 1 : log10(rank) + 1);
		int32_t whitespaceChars = maxScoreStringLength - lengthOfRankInteger;
		int32_t lastWhitespaceIndex;
		char8_t leadingRankWhitespace[SMALL_BUFFER];
		char8_t rankAsString[SMALL_BUFFER];

		// Set the color for each high score entry
		(newHighScoreIndex == i)
			? glColor3f(highlightColor.red, highlightColor.green, highlightColor.blue)
			: glColor3f(standardColor.red, standardColor.green, standardColor.blue);

		for (lastWhitespaceIndex = 0; lastWhitespaceIndex < whitespaceChars; ++lastWhitespaceIndex)
		{
			// Build the leading whitespace string
			leadingRankWhitespace[lastWhitespaceIndex] = ' ';
		}
		leadingRankWhitespace[lastWhitespaceIndex] = '\0';

		// Convert each rank from an integer to a string
		sprintf_s(rankAsString, "%d", rank);

		glPushMatrix();
		glTranslatef(HIGHSCORE_POSITION.x + RANK_OFFSET.x, 300.0f - (vertPadding * i), 0.0f);
		for (int32_t j = 0; j < lastWhitespaceIndex; ++j)
		{
			// Display the leading whitespace before each rank, if needed
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, leadingRankWhitespace[j]);
		}
		for (int32_t j = 0; j < lengthOfRankInteger; ++j)
		{
			// Display each rank
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, rankAsString[j]);
		}
		glPopMatrix();

		// Display the name
		lengthOfString = name.length();
		glPushMatrix();
		glScalef(1.0f, 1.0f, 1.0f);
		glTranslatef(HIGHSCORE_POSITION.x + NAME_OFFSET.x, 300.0f - (vertPadding * i), 0.0f);
		for (int32_t j = 0; j < lengthOfString; ++j)
		{
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, name[j]);
		}
		glPopMatrix();

		// Display the score
		lengthOfString = (int32_t)strlen(scoreBuffer);
		glPushMatrix();
		glScalef(1.0f, 1.0f, 1.0f);
		glTranslatef(HIGHSCORE_POSITION.x + TIME_OFFSET.x -(lengthOfString * 52), 300.0f - (vertPadding * i), 0.0f);
		for (int32_t j = 0; j < lengthOfString; ++j)
		{
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, scoreBuffer[j]);
		}
		glPopMatrix();
	}

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
	for (int32_t i = 0; i < lengthOfString; ++i)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, phaseText[i]);
	}
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void UIManagerC::formatTime(int32_t time, char8_t* formattedTime)
{
	char8_t minutesString[SMALL_BUFFER];
	char8_t secondsString[SMALL_BUFFER];
	char8_t millisString[SMALL_BUFFER];
	char8_t timerString[LARGE_BUFFER];
	memset(timerString, 0x00, strlen(timerString));

	int32_t millis = (time % 1000) / 10;
	int32_t seconds = (time / 1000) % 60;
	int32_t minutes = (time / 1000) / 60;
	_itoa_s(millis, millisString, 10);
	_itoa_s(seconds, secondsString, 10);
	_itoa_s(minutes, minutesString, 10);

	strcat_s(timerString, minutesString);
	strcat_s(timerString, ":");
	if (seconds < 10)
	{
		strcat_s(timerString, "0");
	}
	strcat_s(timerString, secondsString);
	strcat_s(timerString, ":");
	if (millis < 10)
	{
		strcat_s(timerString, "0");
	}

	strcat_s(timerString, millisString);

	strcpy(formattedTime, timerString);
}