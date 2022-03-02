#include "World.h"
#include "Map.h"
#include "Enemy.h"
#include "Play.h"
#include "Tower.h"
#include "Bullet.h"
void World::Run()
{
	DWORD initial = HAPI.GetTime();
	DWORD newTime;
	const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();
	start.first = 0;
	start.second = 392;
	bool found = false;
	int tick{ 0 };
	std::pair<int, int> thing{};
	thing.first = 178;
	thing.second = 392;
	EnemyPath.push_back(thing);
	thing.second = 175;
	EnemyPath.push_back(thing);
	thing.first = 395;
	EnemyPath.push_back(thing);
	thing.second = 464;
	EnemyPath.push_back(thing);
	thing.first = 679;
	EnemyPath.push_back(thing);
	thing.second = 321;
	EnemyPath.push_back(thing);
	thing.first = 1080;
	EnemyPath.push_back(thing);//enemypath in which they need to follow
	Play play;
	Entities.push_back(new Map());
	for (int i = 0; i < 200; i++)
	{
		Entities.push_back(new Enemy(1, false, 0, 1, 1, "Data\\TowerDefense\\Enemys\\Enemy1.png", start, EnemyPath, false));
	}
	for (int i = 0; i < 100; i++)
	{
		Entities.push_back(new Tower("Data\\TowerDefense\\Towers\\Tower1.png", start, false, 0, 0));
	}//initialising all memory needed
	while (HAPI.Update())
	{
		newTime = HAPI.GetTime();//contorlling tick speed
		if (newTime - initial == 1)
		{
			tick++;
			int temp = waveValue;
			const HAPI_TMouseData& MouseData = HAPI.GetMouseData();
			int Mousex = MouseData.x;
			int Mousey = MouseData.y;
			if (MouseData.leftButtonDown&& tick == 20)
			{
				std::cout << Mousex << "," << Mousey << std::endl;
				if (Mousex >= play.GetPosition().first && Mousex <= play.GetPosition().first+32)
				{
					if (Mousey >= play.GetPosition().second && Mousey <= play.GetPosition().second + 32)
					{
						click = true;
						if (waveValue != 0)
						{
							Wave();//spawns wave if the button is clicked
						}
					}
				}
				for (GameObject* entity : Entities)
				{
					if (entity->IsCollected())
					{
						entity->SetDown();//allows the user to place towers
					}
				}
			}
			if (click&& waveValue == temp)
			{
				Wave();//spawns a wave
			}
			if (waveValue == 0)//increases the waveValue
			{
				click = false;
				wave++;
				waveValue = 5 * wave;
			}
			if (keyData.scanCode[HK_NUMPAD1])//if you want a tier 1 tower
			{
				for (GameObject* entity : Entities)
				{
					if (entity->GetSide() == 1)
					{
						if (entity->GetType() == 3)
						{
							if (!entity->ReturnAlive()&&!found&& tick == 20)
							{
								if (PlayerMoney >= 50)
								{
									entity->Spawn("Data\\TowerDefense\\Towers\\Tower1.png", std::pair<float, float>{Mousex, Mousey}, 200, 30, 1, start);
									PlayerMoney -= 50;
									found = true;
								}
							}
						}
					}
				}
				found = false;
			}
			if (keyData.scanCode[HK_NUMPAD2])//if you want a tier 2 tower
			{
				for (GameObject* entity : Entities)
				{
					if (entity->GetSide() == 1)
					{
						if (entity->GetType() == 3)
						{
							if (!entity->ReturnAlive() && !found && tick == 20)
							{
								if (PlayerMoney >= 100)
								{
									entity->Spawn("Data\\TowerDefense\\Towers\\Tower2.png", std::pair<float, float>{Mousex, Mousey}, 100, 40, 2, start);
									PlayerMoney -= 100;
									found = true;
								}
							}
						}
					}
				}
				found = false;
			}
			if (keyData.scanCode[HK_NUMPAD3])//if you want a tier 3 tower
			{
				for (GameObject* entity : Entities)
				{
					if (entity->GetSide() == 1)
					{
						if (entity->GetType() == 3)
						{
							if (!entity->ReturnAlive() && !found && tick == 20)
							{
								if (PlayerMoney >= 150)
								{
									entity->Spawn("Data\\TowerDefense\\Towers\\Tower3.png", std::pair<float, float>{Mousex, Mousey}, 500, 40, 3, start);
									PlayerMoney -= 150;
									found = true;
								}
							}
						}
					}
				}
				found = false;
			}
			if (keyData.scanCode[HK_NUMPAD4])//if you want a tier 4 tower
			{
				for (GameObject* entity : Entities)
				{
					if (entity->GetSide() == 1)
					{
						if (entity->GetType() == 3)
						{
							if (!entity->ReturnAlive() && !found && tick == 20)
							{
								if (PlayerMoney >= 200)
								{
									entity->Spawn("Data\\TowerDefense\\Towers\\Tower4.png", std::pair<float, float>{Mousex, Mousey}, 300, 20, 4, start);
									PlayerMoney -= 200;
									found = true;
								}
							}
						}
					}
				}
				found = false;
			}
			for (GameObject* entity : Entities)//Looping from all gameObjects
			{
				if (entity->ReturnAlive())
				{
					std::pair<int, int> Flags = system.ClipCheck(entity);//check if the entity is clipped
					if (Flags.first == 0 && Flags.second == 0)
					{
						if (entity->GetType() == 10)
						{
							std::cout << "yes";
						}
						system.Render(entity->GetImage(), entity->GetPosition(), entity->ReturnHeight(), entity->ReturnWidth());//render if not clipped
					}
					else
					{
						if (entity->GetSide() == 2)// if entity is an enemy they haev reached the end of the track destroy the entity and remove the health
						{
							health-= entity->GetHealth();
							entity->Dead();
						}
						else
						{
							system.RenderClip(Flags.first, Flags.second, entity->GetPosition(), entity->GetImage(), entity->ReturnHeight(), entity->ReturnWidth());//cilp the entity
						}
					}
					entity->Move(Mousex, Mousey);
					entity->Update(Entities);
				}
			}
			system.Render(play.GetImage(), play.GetPosition(), play.ReturnHeight(), play.ReturnWidth());//rendering play button
			text = std::to_string(PlayerMoney);
			HAPI.RenderText(800, 25, HAPI_TColour::BLACK, "Money:"+text, 20, eRegular);
			text = std::to_string(health);
			HAPI.RenderText(800, 50, HAPI_TColour::BLACK, "Health:" + text, 20, eRegular);
			text = std::to_string(wave);
			HAPI.RenderText(800, 75, HAPI_TColour::BLACK, "Wave:" + text, 20, eRegular);//rendering all text entitys^^^
			if (health <= 0 || wave >=40)//gameover
			{
				HAPI.Close();
			}
		}
		if (tick == 20)
		{
			tick = 0;
		}
		initial = newTime;
		newTime = HAPI.GetTime();
	}
}
World::~World()
{
	for (GameObject* entity : Entities)
	{
		delete entity;
	}
}
void World::Wave()//calculates the amount of minions and which ones need to be spawned
{
	if (counter == 0)
	{
		if (wave == 2)
		{
			level = 2;
		}
		if (wave == 10)
		{
			level = 3;
		}
		if (wave == 20)
		{
			level = 4;
		}
		if (wave == 30)
		{
			level= 5;
		}
		for (GameObject* entity : Entities)
		{
			if (entity->GetSide() == 2)
			{
				bool foundDead{ false };
				if (!entity->ReturnAlive())
				{
					foundDead = true;
					if (waveValue >= level)
					{
						if (level >= 4)
						{
							entity->Ressurect(level, false, 0, 1, level, "Data\\TowerDefense\\Enemys\\Enemy" + std::to_string(level) + ".png", start, true);
							counter = 20;
						}
						else
						{
							entity->Ressurect(level, false, 0, 1, level, "Data\\TowerDefense\\Enemys\\Enemy" + std::to_string(level) + ".png", start, true);
							counter = 20;
						}
						waveValue = waveValue - level;
					}
					else
					{
						if (waveValue == 0);
						else
						{
							int tempLevel = level - 1;
							while (tempLevel > waveValue)
							{
								tempLevel--;
							}
							if (tempLevel >= 4)
							{
								entity->Ressurect(level, true, 0, 1, tempLevel, "Data\\TowerDefense\\Enemys\\Enemy" + std::to_string(tempLevel) + ".png", start, true);
								counter = 20;
							}
							else
							{
								entity->Ressurect(level, false, 0, 1, tempLevel, "Data\\TowerDefense\\Enemys\\Enemy" + std::to_string(tempLevel) + ".png", start, true);
								counter = 20;
							}
							waveValue = waveValue - tempLevel;

						}
						
					}
				}
				if (foundDead == true)
				{
					foundDead = false;
					break;
				}
			}
		}
	}
	counter--;
}
//Enemy path = [(178,392),(178,175),(395,175),(395,464),(679,464),(679,321),(1080,321)]
//Top Border Path =[(0,362),(146,362),(146,148),(426,148),(426,437),(652,437),(652,293),(1080,293)]
//Bottom Border Path =[(0,427),(210,427),(210,213),(362,213),(362,497),(714,497),(714,359),(1080,359)]