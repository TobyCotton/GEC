#include "GameObject.h"

void GameObject::Move(float x, float y)
{
}

int GameObject::GetHealth()
{
    return m_health;
}

bool GameObject::GetDown()
{
    return m_down;
}

void GameObject::SetDown()
{
    m_down = true;
    m_collected = false;
}



void GameObject::Dead()
{
    m_alive = false;
}

bool GameObject::ReturnAlive()
{
    return m_alive;
}

void GameObject::SetHealth(int health)
{
    m_health = health;
}

int GameObject::ReturnWidth()
{
    return tw;
}

int GameObject::ReturnHeight()
{
    return th;
}

bool GameObject::IsCollected()
{
    return m_collected;
}

void GameObject::Spawn(std::string frame, std::pair<float, float> Coords, int range, int firerate, int towerType, std::pair<float, float> enemyCoords)
{
}

void GameObject::Ressurect(int health, bool respawn, int armour, float speed, int level, std::string frame, std::pair<float, float> Coords, bool alive)
{
}


int GameObject::GetSide()
{
    return m_side;
}

BYTE* GameObject::GetImage()
{
    return m_frame;
}

std::pair<float, float> GameObject::GetPosition()
{
    return m_Coords;
}

void GameObject::SetPosition(std::pair<float, float> set)
{
    m_Coords = set;
}
