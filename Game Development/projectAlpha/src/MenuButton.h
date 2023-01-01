#pragma once
#include "SDLGameObject.h"
#include "gameObjectFactory.h"

enum button_states
{
	MOUSE_OUT = 1, 
	MOUSE_OVER = 2,
	CLICKED = 3
};

class MenuButton : public SDLGameObject
{
private:
	
	void (*m_callback)();
	int callbackID;
	bool mouseButtonRelease = true;

	//for implementing action upon mouse release
	bool justClicked = false;

public:
	//constructor
	MenuButton();

	virtual void load(const LoaderParams* pParams);
	//core functions
	virtual void draw();
	virtual void update();
	virtual void clean();
	void setCallBack(void(*callback)());
	int getCallBackID();

	//helping functions
	virtual void onMouseButtonDown();
	virtual void onMouseButtonUp();
	virtual void onMouseHover();
};

class MenuButtonCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new MenuButton();
	}
};