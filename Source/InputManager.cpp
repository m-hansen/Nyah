#include "pch.h"

extern GL_Window*	g_window;
extern Keys*		g_keys;

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
	if (g_keys->keyDown[VK_RETURN])
	{
		g_keys->keyDown[VK_RETURN] = FALSE;
		return true;
	}
	return false;
}

bool8_t InputManagerC::GetResetButton()
{
	if (g_keys->keyDown[VK_RETURN])
	{
		g_keys->keyDown[VK_RETURN] = FALSE;
		return true;
	}
	return false;
}

bool8_t InputManagerC::GetDifficultyButton()
{
	if (g_keys->keyDown[VK_SPACE])
	{
		g_keys->keyDown[VK_SPACE] = FALSE;
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

bool8_t InputManagerC::GetBackButton()
{
	if (g_keys->keyDown[VK_BACK])
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

bool8_t InputManagerC::QuitPressed()
{
	if (g_keys->keyDown[VK_ESCAPE])								// Is ESC Being Pressed?
	{
		return true;						// Terminate The Program
	}
	return false;
}

void InputManagerC::QuitGame()
{
	TerminateApplication(g_window);
}
