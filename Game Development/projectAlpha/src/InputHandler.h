#pragma once
#include <SDL.h>

class InputHandler
{
private:
	static InputHandler* s_pInstance;
	
	InputHandler() {}
	~InputHandler() {}

public:
	static InputHandler* instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
			return s_pInstance;
		}

		return s_pInstance;
	}

	void update();
	void clean();

};