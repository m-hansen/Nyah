#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <gl\glut.h>
#include <assert.h>
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "UIManager.h"
#include "random.h"

#include "soil.h"

UIManagerC* UIManagerC::sInstance = NULL;

UIManagerC *UIManagerC::CreateInstance()
{
	if (sInstance != NULL)return sInstance;
	else

		sInstance = new UIManagerC();
	return sInstance;
}

void UIManagerC::init()
{
	strcpy(title, "NYAH");
	strcpy(startPrompt, "PRESS SPACE TO PLAY");
	strcpy(gameOverText, "Game Over");
	strcpy(restartPrompt, "Press ENTER to restart");
	mCurrentTime = 0;
}

void UIManagerC::reset()
{
	mCurrentTime = 0;
}

void UIManagerC::update(DWORD milliseconds)
{
	mCurrentTime += milliseconds;
}

void UIManagerC::renderScore()
{
	char8_t minutesString[SMALL_BUFFER];
	char8_t secondsString[SMALL_BUFFER];
	char8_t millisString[SMALL_BUFFER];
	char8_t timerString[LARGE_BUFFER];
	memset(timerString, 0x00, strlen(timerString));

	int32_t millis = (mCurrentTime % 1000)/10;
	int32_t seconds = (mCurrentTime /1000) % 60;
	int32_t minutes = (mCurrentTime/1000) / 60;
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
	int32_t lengthOfString = (int32_t)strlen(title);
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
	lengthOfString = (int32_t)strlen(startPrompt);
	glTranslatef(-(lengthOfString * 52), -500.0f, 0.0f);
	for (int i = 0; i < lengthOfString; i++)
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

	glTranslatef(-(lengthOfString * 52), 100.0f, 0.0f);
	for (int i = 0; i < lengthOfString; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, gameOverText[i]);
	}
	glPopMatrix();

	// Restart prompt
	glPushMatrix();
	lengthOfString = (int32_t)strlen(restartPrompt);
	glTranslatef(-(lengthOfString * 52), -500.0f, 0.0f);
	for (int i = 0; i < lengthOfString; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, restartPrompt[i]);
	}
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
}