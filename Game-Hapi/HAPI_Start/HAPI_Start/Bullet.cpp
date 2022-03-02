#include "Bullet.h"

//is not used hopefully added in the future

void Bullet::Update(std::vector<GameObject*> Entities)
{
}

Bullet::Bullet(std::string frame, bool piercing, int tower, std::pair<float, float> velocity)
{
	if (!HAPI.LoadTexture(frame, &m_frame, tw, th))
	{
		HAPI.UserMessage("Missing Tower texture", "Error");
		HAPI.Close();
	}
	m_piercing = piercing;
	m_tower = tower;
	m_side = 1;
	m_velocity = velocity;
	m_type = 10;
}

int Bullet::GetType()
{
    return m_type;
}

void Bullet::Spawn(std::string frame, std::pair<float, float> Coords, int range, int firerate, int towerType, std::pair<float, float> enemyCoords)
{
	float length = sqrt(pow(Coords.first - enemyCoords.first, 2) + pow(Coords.second - enemyCoords.second, 2));
	m_alive = true;
	m_Coords = Coords;
	m_destination = enemyCoords;
	if (!HAPI.LoadTexture(frame, &m_frame, tw, th))
	{
		HAPI.UserMessage("Missing Tower texture", "Error");
		HAPI.Close();
	}
	m_velocity.first = (Coords.first - enemyCoords.first) / length;
	m_velocity.second = (Coords.second - enemyCoords.second) / length;
}

void Bullet::Move(float x, float y)
{
	m_Coords.first += m_velocity.first;
	m_Coords.second += m_velocity.second;
}
