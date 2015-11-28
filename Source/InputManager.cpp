#include <windows.h>											// Header File For Windows
#include <gl/gl.h>														// Header File For The OpenGL32 Library
#include <gl/glu.h>														// Header File For The GLu32 Library
#include <gl\glut.h>
#include "openglframework.h"
#include "baseTypes.h"
#include "InputManager.h"
InputManagerC* InputManagerC::sInstance = NULL;

InputManagerC *InputManagerC::CreateInstance()
{
	if (sInstance != NULL)return sInstance;
	else

	sInstance = new InputManagerC();
	return sInstance;
}

bool8_t InputManagerC::GetStartButton()
{
	if (g_keys->keyDown[VK_SPACE])
	{
		//KeyReleased(g_window, VK_SPACE);
		return true;
	}
	return false;
}

bool8_t InputManagerC::GetResetButton()
{
	if (g_keys->keyDown[VK_RETURN])
	{
		//KeyReleased(g_window, VK_RETURN);
		return true;
	}
	return false;
}

bool8_t InputManagerC::GetClockwiseRotationButton()
{
	if (g_keys->keyDown[VK_RIGHT])
	{
		return true;
	}
	return false;
}

bool8_t InputManagerC::GetCounterClockwiseRotationButton()
{
	if (g_keys->keyDown[VK_LEFT])
	{
		return true;
	}
	return false;
}

bool8_t InputManagerC::DebugPlayerKill()
{
	if (g_keys->keyDown[VK_F3])
	{
		return true;
	}
	return false;
}
