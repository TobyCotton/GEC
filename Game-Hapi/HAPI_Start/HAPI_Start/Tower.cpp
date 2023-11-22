#include "Tower.h"

Tower::Tower(std::string frame,std::pair<float, float> Coords, bool alive, int range,int firerate)//initialises tower variables
{
	if (!HAPI.LoadTexture(frame, &m_frame, tw, th))
	{
		HAPI.UserMessage("Missing Tower texture", "Error");
		HAPI.Close();
	}
	m_Coords = Coords;
	m_alive = alive;
	m_range = range;
	m_firerate = firerate;
	m_side = 1;
	m_type = 3;
}

void Tower::Spawn(std::string frame, std::pair<float, float> Coords, int range, int firerate, int towerType, std::pair<float, float> enemyCoords)//spawns the tower once its been clicked
{
	if (!HAPI.LoadTexture(frame, &m_frame, tw, th))
	{
		HAPI.UserMessage("Missing Tower texture", "Error");
		HAPI.Close();
	}
	m_Coords = Coords;
	m_alive = true;
	m_range = range;
	m_firerate = firerate;
	m_collected = true;
	m_towerType = towerType;
}

void Tower::Move(float x, float y)//moves tower to mouse positions if it isnt down
{
	if (!m_down)
	{
		m_Coords.first = x;
		m_Coords.second = y;
	}
}

int Tower::GetType()
{
	return m_type;
}

void Tower::Update(std::vector<GameObject*> Entities)//decides whether it should shoot
{
	m_tick++;
	if (m_down == true)
	{
		if (m_tick >= 100)
		{
			m_tick = 0;
			Shoot(Entities);
		}
	}
}

void Tower::Shoot(std::vector<GameObject*> Entities)
{
	bool flag2 = false;
	for (GameObject* entity2 : Entities)
	{
		if (entity2->GetSide() == 2 && flag2 == false)
		{
			float length = sqrt(pow(m_Coords.first - entity2->GetPosition().first, 2) + pow(m_Coords.second - entity2->GetPosition().second, 2));
			if (length <= m_range)
			{
				if (entity2->ReturnAlive())
				{
					flag2 = true;
					if (entity2->GetHealth() != 1)//checks all variables required to shoot an enemy and that it isnt a red enemy
					{
						entity2->Ressurect(entity2->GetHealth(), true, false, 1, entity2->GetHealth() - 1, "Data\\TowerDefense\\Enemys\\Enemy" + std::to_string(entity2->GetHealth() - 1) + ".png", entity2->GetPosition(), true);
						entity2->SetHealth(entity2->GetHealth() - 1);
					}
					else//if red enemy kill it
					{
						entity2->Dead();
					}
				}
			}
		}
	}


}
