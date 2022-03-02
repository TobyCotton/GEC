#include "Play.h"

void Play::Update(std::vector<GameObject*> Entities)
{
}

Play::Play()
{
	m_side = 0;
	if (!HAPI.LoadTexture("Data\\TowerDefense\\Play.png", &m_frame, tw, th))// Loading all textures for the play button
	{
		HAPI.UserMessage("Missing Play texture", "Error");
		HAPI.Close();
	}
	m_Coords.first = 1000;
	m_Coords.second = 600;
	m_alive = true;
	m_type = 0;
}

int Play::ReturnWidth()
{
	return tw;
}

int Play::ReturnHeight()
{
	return th;
}

BYTE* Play::GetImage()
{
	return m_frame;
}

std::pair<float, float> Play::GetPosition()
{
	return m_Coords;
}

int Play::GetType()
{
	return m_type;
}

