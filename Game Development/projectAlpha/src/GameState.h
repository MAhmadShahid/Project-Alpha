#pragma once

#include <iostream>
#include <vector>

enum game_states
{
	MENU,
	PLAY,
	GAMEOVER
};

//menu, transition screen, different levels
class GameState
{

public:
	virtual void update() = 0;
	virtual void render() = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual std::string getStateID() const = 0;

protected:
	std::vector<std::string> m_textureIDList;

};
