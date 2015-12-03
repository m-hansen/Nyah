#define STATE_MANAGER_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <string>
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <gl\glut.h>
#include <assert.h>
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "spriteManager.h"
#include "PhaseManager.h"
#include "random.h"

#include "soil.h"

SpriteManagerC* SpriteManagerC::sInstance=NULL;

struct RenderData
{
	GLfloat uLeft, uRight, vTop, vBottom;
	GLfloat xLeft, xRight, yTop, yBottom;
	GLubyte r, g, b, a;
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
	mBulletSpriteTexture = loadTexture("Sprites/bullets2.png");
	mPlayerSpriteTexture = loadTexture("Sprites/playersheet.png");
	mBackgroundTexture = loadTexture("Sprites/bg2.png");

	colorStep = 0;
	colorDelta = 1;
	angle = 0;
	rotationDirection = 1;
}

GLuint SpriteManagerC::loadTexture(char8_t* fileToLoad)
{
	GLuint textureID = SOIL_load_OGL_texture(fileToLoad, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	return textureID;
}

void SpriteManagerC::update(DWORD milliseconds)
{
	mCurrentTime += milliseconds;

	if (mCurrentTime - mLastColorUpdateTime > COLOR_UPDATE_DELTA_TIME)
	{
		mLastColorUpdateTime = mCurrentTime;
		if (colorStep == 0)
		{
			colorDelta = 1;
		}
		else if (colorStep == 255)
		{
			colorDelta = -1;
		}
		colorStep = (colorStep + colorDelta);
	}
	if (mCurrentTime - mLastAngleUpdateTime > ANGLE_UPDATE_DELTA_TIME)
	{
		mLastAngleUpdateTime = mCurrentTime;
		int32_t reverseChance = getRangedRandom(0, 5000);
		if (reverseChance > 5 && reverseChance < 10)
		{
			rotationDirection *= -1;
		}

		float_t rotationSpeed = 0.0f;
		switch (PhaseManagerC::GetInstance()->getPhase())
		{
			case Phase::NYAH_TWO:
				rotationSpeed = ROT_SPEED_SLOW;
				break;
			case Phase::NYAH_THREE:
			case Phase::NYAH_FOUR:
				rotationSpeed = ROT_SPEED_MEDIUM;
				break;
			case Phase::NYAH_FIVE:
				rotationSpeed = ROT_SPEED_FAST;
				break;
		}

		angle += rotationDirection * rotationSpeed;
	}

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

	//Set color
	quad.r = 0xFF - colorStep;
	quad.g = 0x00;
	quad.b = colorStep;
	quad.a = 0xFF;

	OGL_Render2(quad, mBackgroundTexture);
}

void SpriteManagerC::renderBullet(BulletAnimationState state, BulletColor color, int32_t animationFrameNo, GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat radius)
{
	struct RenderData quad;

	GLfloat u, v;
	u = animationFrameNo * (1.0 / 8.0);
	if (color == RED)
	{
		if (state == GLOWING)
		{
			v = 0.25f;
		}
		else if (state == SHRINKING)
		{
			v = 0.0f;
		}
	}
	else if(color == BLUE)
	{
		if (state == GLOWING)
		{
			v = 0.75f;
		}
		else if (state == SHRINKING)
		{
			v = 0.5f;
		}
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

	//Set color
	quad.r = 0xFF;
	quad.g = 0xFF;
	quad.b = 0xFF;
	quad.a = 0xFF;

	OGL_Render(quad, mBulletSpriteTexture);
}

void SpriteManagerC::renderPlayer(int32_t animationFrameNo, GLfloat left, GLfloat right, GLfloat top, GLfloat bottom)
{
	GLfloat u = animationFrameNo * (1.0 / 4.0);

	struct RenderData quad;

	// Set UV Coordinates
	quad.uLeft = u;
	quad.uRight = u + (1.0 / 4.0);
	quad.vTop = 0;
	quad.vBottom = 1;

	// Set position coordinates
	quad.xLeft = left;
	quad.xRight = right;
	quad.yTop = top;
	quad.yBottom = bottom;

	// Set color
	quad.r = 0xFF;
	quad.g = 0xFF;
	quad.b = 0xFF;
	quad.a = 0xFF;

	OGL_Render(quad, mPlayerSpriteTexture);
}

void SpriteManagerC::OGL_Render(struct RenderData quad, GLuint textureID)
{
	glPushMatrix();
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);

	glColor4ub(quad.r, quad.g, quad.b, quad.a);

	glTexCoord2f(quad.uLeft, quad.vTop);
	glVertex3f(quad.xLeft, quad.yTop, 0.0);

	glTexCoord2f(quad.uRight, quad.vTop);
	glVertex3f(quad.xRight, quad.yTop, 0.0);

	glTexCoord2f(quad.uRight, quad.vBottom);
	glVertex3f(quad.xRight, quad.yBottom, 0.0);

	glTexCoord2f(quad.uLeft, quad.vBottom);
	glVertex3f(quad.xLeft, quad.yBottom, 0.0);

	glEnd();
	glPopMatrix();
}

void SpriteManagerC::OGL_Render2(struct RenderData quad, GLuint textureID)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);

	glColor4ub(quad.r, quad.g, quad.b, quad.a);

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
