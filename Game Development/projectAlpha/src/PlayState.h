#pragma once

#include "GameState.h"
#include "GameObject.h"
#include "Level.h"
#include <iostream>
#include <vector>
#include <map>
#include "Vector2D.h"
#include "Region2.h"

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID; }


private:
	static const std::string s_playID;
	std::vector<GameObject*> playStateObjects;
	std::vector<std::string> m_textureIDList;
	//std::map<std::string, std::vector<Region2>> collisionRegions;

	Level* pLevel;
};
