#include "Enemy1.h"

Enemy1::Enemy1()
{
	if (!HAPI.LoadTexture("Data\\TowerDefense\\Enemys\\Enemy1.png", &frame, tw, th))// Loading all textures from file for left animation
	{
		HAPI.UserMessage("Missing Enemy texture", "Error");
		HAPI.Close();
	}
	side = 2;
	Coords.first = 0;
	Coords.second = 392;
	health = 1;
	armour = 0;
	speed = 1.0f;
	level = 1;
	flying = false;
}
