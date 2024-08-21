#pragma once
#include <list>
#include <string>
#include "AEEngine.h"

class Animation
{
private:
	std::string name;
	std::list<std::pair<float, AEGfxTexture*>> frame;

public:
	Animation(std::string _name);
	~Animation();

	void AddFrame(float, std::string);
	void SaveAnimation();
};
