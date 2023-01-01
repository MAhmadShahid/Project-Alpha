#pragma once

#include "GameState.h"
#include "GameObject.h"
#include <iostream>
#include <vector>

class MenuState : public GameState
{
private:
	static const std::string menuID;
	std::vector<GameObject*> m_menuObjects;

protected:
	typedef void(*Callback)();

	std::vector<Callback> m_callbacks;
	std::vector<std::string> m_textureIDList;
	virtual void setCallBacks(const std::vector<Callback>& callback) = 0;

public:

	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit(); 

	virtual std::string getStateID() const { return menuID; }

};