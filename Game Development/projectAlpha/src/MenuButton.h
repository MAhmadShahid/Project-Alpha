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
public:
	MenuButton(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();
};