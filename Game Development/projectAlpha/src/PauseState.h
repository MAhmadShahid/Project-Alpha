#pragma once

#include "GameState.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include <iostream>
#include <vector>

class PauseState : public GameState
{
private:
	static const std::string s_pauseID;
	void(*m_callback)();
	std::vector<GameObject*> pauseStateObjects;

public:
	virtual bool onEnter();
	virtual bool onExit();

	virtual void update();
	virtual void render();


	static void s_pauseToMainMenu();
	static void s_backToPlay();

	virtual std::string getStateID() const{ return s_pauseID; }
};