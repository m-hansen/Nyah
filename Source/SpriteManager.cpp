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

struct RenderData
{
	GLfloat uLeft, uRight, vTop, vBottom;
	GLfloat xLeft, xRight, yTop, yBottom;
};

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
	mBulletSpriteTexture = SOIL_load_OGL_texture("Sprites/bullets2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mBackgroundTexture = SOIL_load_OGL_texture("Sprites/bg.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}

void SpriteManagerC::renderBackground()
{
	struct RenderData quad;

	//Set UV Coordinates
	quad.uLeft = 0;
	quad.uRight = 1;
	quad.vTop = 0;
	quad.vBottom = 1;

	//Set position coordinates
	quad.xLeft = -2048.0f;
	quad.xRight = 2048.0f;
	quad.yTop = -2048.0f;
	quad.yBottom = 2048.0f;

	OGL_Render(quad, mBackgroundTexture);
}

void SpriteManagerC::renderBullet(BulletColor color, int32_t animationFrameNo, GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat radius)
{
	struct RenderData quad;

	GLfloat u, v;
	u = animationFrameNo * (1.0 / 8.0);
	if (color == RED)
	{
		v = 0.25f;
	}
	else if(color == BLUE)
	{
		v = 0.75f;
	}

	//Set UV Coordinates
	quad.uLeft = u;
	quad.uRight = u + (1.0 / 8.0);
	quad.vTop = v;
	quad.vBottom = v + (1.0 / 4.0);

	//Set position coordinates
	quad.xLeft = left - radius;
	quad.xRight = right - radius;
	quad.yTop = top - radius;
	quad.yBottom = bottom - radius;

	OGL_Render(quad, mBulletSpriteTexture);
}

void SpriteManagerC::OGL_Render(struct RenderData quad, GLuint textureID)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);

	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);

	glTexCoord2f(quad.uLeft, quad.vTop);
	glVertex3f(quad.xLeft, quad.yTop, 0.0);

	glTexCoord2f(quad.uRight, quad.vTop);
	glVertex3f(quad.xRight, quad.yTop, 0.0);

	glTexCoord2f(quad.uRight, quad.vBottom);
	glVertex3f(quad.xRight, quad.yBottom, 0.0);

	glTexCoord2f(quad.uLeft, quad.vBottom);
	glVertex3f(quad.xLeft, quad.yBottom, 0.0);

	glEnd();
}
