#pragma once
#include "SDLGameObject.h"

enum button_states
{
	MOUSE_OUT, 
	MOUSE_OVER,
	CLICKED
};

class MenuButton : public SDLGameObject
{
private:
	
	void (*m_callback)();
	bool justClicked = false;
	bool mouseButtonRelease = true;

public:
	//constructor
	MenuButton(const LoaderParams* pParams, void(*callback)());

	//core functions
	virtual void draw();
	virtual void update();
	virtual void clean();

	//helping functions
	virtual void onMouseButtonDown();
	virtual void onMouseButtonUp();
	virtual void onMouseHover();
};