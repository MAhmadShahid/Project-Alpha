#pragma once

#include "GameState.h"
#include "GameObject.h"
#include <iostream>
#include <vector>

class MenuState : public GameState
{
public:

	static void s_menuToPlay();
	static void s_exitFromMenu();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit(); 

	virtual std::string getStateID() const { return menuID; }


private:	
	static const std::string menuID;
	std::vector<GameObject*> m_menuObjects;
};