#pragma once
#ifndef __GAMEOVERSTATE__
#define __GAMEOVERSTATE__

#include <iostream>
#include <vector>
#include "GameState.h"
#include "GameObject.h"
#include "MenuState.h"

class GameOverState : public MenuState
{
private:
	static const std::string s_gameOverID;
	std::vector<GameObject*> m_gameObjects;
	
	static void s_gameOverToMain();
	static void s_restartPlay();
	virtual void setCallBacks(const std::vector<Callback>& callback);

public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_gameOverID; }


};

#endif