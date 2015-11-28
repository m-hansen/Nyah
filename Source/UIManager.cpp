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
}

void UIManagerC::renderLogo()
{
	int32_t lengthOfString = (int32_t)strlen(title);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glScalef(4.0f, 4.0f, 4.0f);

	glTranslatef(-(lengthOfString * 52), 100.0f, 0.0f);
	for (int i = 0; i < lengthOfString; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, title[i]);
	}
	glPopMatrix();

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