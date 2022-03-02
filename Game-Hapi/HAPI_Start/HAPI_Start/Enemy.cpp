#include "Enemy.h"
int Enemy::GetArmour()
{
	return m_armour;
}
void Enemy::Ressurect(int health, bool respawn, int armour, float speed, int level, std::string frame, std::pair<float, float> Coords, bool alive)//respawning a unit at the start or at its current position depending on why its needed
{
	if (!HAPI.LoadTexture(frame, &m_frame, tw, th))// Loading all textures from file for left animation
	{
		HAPI.UserMessage("Missing Enemy texture", "Error");
		HAPI.Close();
	}
	m_alive = alive;
	m_Coords.first = Coords.first;
	m_Coords.second = Coords.second;
	m_health = health;
	m_armour = armour;
	m_speed = speed;
	m_level = level;
	if (respawn == false)
	{
		m_node = 0;
	}
}
void Enemy::SetHealth(int health)
{
	m_health = health;
}
void Enemy::Update(std::vector<GameObject*> Entities)
{
}
Enemy::Enemy(int health, bool flying, int armour, float speed, int level, std::string frame, std::pair<float, float> Coords, std::vector<std::pair<int, int>> EnemyPath,bool alive)//initialising enemy variables
{
	if (!HAPI.LoadTexture(frame, &m_frame, tw, th))// Loading all textures from file for left animation
	{
		HAPI.UserMessage("Missing Enemy texture", "Error");
		HAPI.Close();
	}
	m_alive = alive;
	m_EnemyPath = EnemyPath;
	m_side = 2;
	m_Coords.first = Coords.first;
	m_Coords.second = Coords.second;
	m_health = health;
	m_armour = armour;
	m_speed = speed;
	m_level = level;
	m_flying = flying;
	m_type = 2;
}
int Enemy::GetLevel()
{
	return m_level;
}
void Enemy::Move(float x, float y)//navigates the path set out in enemy path
{
	if (m_Coords.second > m_EnemyPath[m_node].second)
	{
		if (m_Coords.first == m_EnemyPath[m_node].first && m_Coords.second == m_EnemyPath[m_node].second)
		{
			m_node++;
			if (m_direction == 0)
			{
				m_direction = 1;// a flag for the direction it should be going in
			}
			else
			{
				m_direction = 0;// a flag for the direction it should be going in
			}
		}
	}
	else
	{
		if (m_Coords.first == m_EnemyPath[m_node].first && m_Coords.second == m_EnemyPath[m_node].second)
		{
			m_node++;
			if (m_direction == 0)
			{
				m_direction = 1;
			}
			else
			{
				m_direction = 0;
			}
		}
	}
	if (m_direction == 0)
	{
		m_Coords.first += m_speed;
	}
	else
	{
		if (m_Coords.second > m_EnemyPath[m_node].second)
		{
			m_Coords.second -= m_speed;
		}
		else
		{
			m_Coords.second += m_speed;
		}
	}
}
int Enemy::GetType()
{
	return m_type;
}
float Enemy::GetSpeed()
{
	return m_speed;
}