#define STATE_MANAGER_CPP
#include "pch.h"

StateManagerC* StateManagerC::sInstance=NULL;


StateManagerC *StateManagerC::CreateInstance()
{
	if(sInstance!=NULL)return sInstance;
	else

	sInstance = new StateManagerC();
	return sInstance;
}
int32_t StateManagerC::getState()
{
	return mCurrentState;
}
void StateManagerC::setState(int32_t state)
{
	mCurrentState = state;
}
void StateManagerC::shutdown()
{
}