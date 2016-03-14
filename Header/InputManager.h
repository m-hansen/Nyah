#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
class InputManagerC
{
public:
	static InputManagerC	*CreateInstance();
	static InputManagerC	*GetInstance() {return sInstance;};
	void					init() { keyDown = false; };
	void					update(DWORD milliseconds){};
	bool8_t GetStartButton();
	bool8_t GetResetButton();
	bool8_t GetClockwiseRotationButton();
	bool8_t GetCounterClockwiseRotationButton();
	bool8_t GetDifficultyButton();
	bool8_t InputManagerC::GetBackButton();
	bool8_t InputManagerC::DebugPlayerKill();
	bool8_t QuitPressed();
	void QuitGame();
//checkout gameframework.cpp
	Coord2D*					getCurrentMousePosition(){};
	//keyboard interface?

private:
	InputManagerC(){};
	bool8_t keyDown;
	static InputManagerC *sInstance;
	DWORD currentTime;
	DWORD keyDownTime;
	
};
#endif