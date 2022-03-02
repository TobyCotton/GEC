#include "Map.h"

void Map::Update(std::vector<GameObject*> Entities)
{
}

Map::Map()
{
	m_side = 0;
	if (!HAPI.LoadTexture("Data\\TowerDefense\\Map.png", &m_frame, tw, th))// Loading all textures for the map
	{
		HAPI.UserMessage("Missing map texture", "Error");
		HAPI.Close();
	}
	m_Coords.first = 0;
	m_Coords.second = 0;
	m_alive = true;
	m_type = 1;
}

int Map::ReturnWidth()
{
	return tw;
}

int Map::ReturnHeight()
{
	return th;
}

BYTE* Map::GetImage()
{
    return m_frame;
}

std::pair<float, float> Map::GetPosition()
{
    return m_Coords;
}

int Map::GetType()
{
	return m_type;
}

