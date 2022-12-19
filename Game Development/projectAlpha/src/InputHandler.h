#pragma once
#include <SDL.h>
#include <vector>
#include "Vector2D.h"

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
private:
	/*Attributes*/
	static InputHandler* s_pInstance;

	//mouse
	std::vector<bool> m_mouseButtonStates;
	Vector2D* m_mousePosition = new Vector2D(0, 0);
	//keyboard
	const Uint8* m_keystate = nullptr;
	
	/*Constructor and Destructor*/
	InputHandler();
	~InputHandler() {}


public:
	static InputHandler* instance();

	//mouse
	Vector2D* getMousePosition() { return m_mousePosition; }
	bool getMouseButtonState(int buttonNumber);

	//keyboard
	bool isKeyDown(SDL_Scancode key);

	void update();
	void clean();

};