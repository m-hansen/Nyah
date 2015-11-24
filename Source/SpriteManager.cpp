#define STATE_MANAGER_CPP
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
#include "spriteManager.h"
#include "random.h"

#include "soil.h"

SpriteManagerC* SpriteManagerC::sInstance=NULL;


SpriteManagerC *SpriteManagerC::CreateInstance()
{
	if(sInstance!=NULL)return sInstance;
	else

	sInstance = new SpriteManagerC();
	return sInstance;
}
void SpriteManagerC::init()
{
	/* load an image file directly as a new OpenGL texture */
	mBulletSpriteTexture = SOIL_load_OGL_texture("Sprites/bullet.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mBackgroundTexture = SOIL_load_OGL_texture("Sprites/spacebg.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}

void SpriteManagerC::renderBackground()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, mBackgroundTexture);
	glBegin (GL_QUADS);

	GLfloat xPositionLeft = -2048.0f;
	GLfloat xPositionRight = 2048.0f;
	GLfloat yPositionTop = -2048.0f;
	GLfloat yPositionBottom = 2048.0f;

	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
	glTexCoord2f(0, 0);
	glVertex3f(xPositionLeft, yPositionTop, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(xPositionRight, yPositionTop, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(xPositionRight, yPositionBottom, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(xPositionLeft, yPositionBottom, 0.0);

	glEnd ();
}

void SpriteManagerC::renderBullet(int32_t animationFrameNo, GLfloat left, GLfloat right, GLfloat top, GLfloat bottom)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mBulletSpriteTexture);
	glBegin(GL_QUADS);

	GLfloat u, v;
	if (animationFrameNo > 7)
	{
		animationFrameNo -= 8;
		v = 0.0;
	}
	else
	{
		v = 0.5;
	}
	u = animationFrameNo * (1.0/8.0);

	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
	glTexCoord2f(u, v);
	glVertex3f(left, top, 0.0);
	glTexCoord2f(u + (1.0/8.0), v);
	glVertex3f(right,top, 0.0);
	glTexCoord2f(u + (1.0/8.0), v + (1.0/2.0));
	glVertex3f(right, bottom, 0.0);
	glTexCoord2f(u, v + (1.0/2.0));
	glVertex3f(left, bottom, 0.0);

	glEnd();
}
