#pragma once
#include "Mario.h"
#include "Graphics.h"


class World
{
private:
	std::vector<GameObject*> Entities;
	const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();
public:
	void Run();
};

