#pragma once

class Layer
{
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void printTileIDs() = 0;

protected:
	virtual ~Layer() {}
};