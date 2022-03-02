#pragma once
#include "Graphics.h"
#include <string>

class World
{
private:
	Graphics system;
	std::pair<float, float> start{};
	std::vector<GameObject*> Entities{};
	bool enemyAlive = false;
	int level = 1;
	int wave = 1;
	bool click = false;
	int counter=0;
	int waveValue = 5;
	std::vector<std::pair<int, int>> EnemyPath{};
	int PlayerMoney = 10000;
	int health = 100;
	const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();
	std::string text{};
public:
	void Run();
	~World();
	void Wave();
};

