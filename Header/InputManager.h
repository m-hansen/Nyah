#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
class InputManagerC
{
public:
	static InputManagerC	*CreateInstance();
	static InputManagerC	*GetInstance() {return sInstance;};
	void					init(){};
	void					update(){};
	bool8_t GetStartButton();
	bool8_t GetResetButton();
//checkout gameframework.cpp
	Coord2D*					getCurrentMousePosition(){};
	//keyboard interface?

private:
	InputManagerC(){};

	static InputManagerC *sInstance;
	
};
#endif