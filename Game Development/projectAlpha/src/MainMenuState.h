#pragma once

#include "GameState.h"
#include "GameObject.h"
#include "MenuState.h"
#include <iostream>
#include <vector>

class MainMenuState : public MenuState
{
private:
	static const std::string menuID;
	std::vector<GameObject*> m_menuObjects;

	static void s_menuToPlay();
	static void s_exitFromMenu();

	virtual void setCallBacks(const std::vector<Callback>& callback);
public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return menuID; }



};