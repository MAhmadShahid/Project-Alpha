#pragma once

#include "GameState.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include <iostream>
#include <vector>
#include "MenuState.h"

class PauseState : public MenuState
{
private:
	static const std::string s_pauseID;
	std::vector<GameObject*> pauseStateObjects;
	
	static void s_pauseToMainMenu();
	static void s_backToPlay();

	virtual void setCallBacks(const std::vector<Callback>& callback);
public:
	virtual bool onEnter();
	virtual bool onExit();

	virtual void update();
	virtual void render();

	virtual std::string getStateID() const{ return s_pauseID; }
};