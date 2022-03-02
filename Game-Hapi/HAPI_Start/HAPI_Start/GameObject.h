#pragma once
#include <HAPI_lib.h>
#include <iostream>

using namespace HAPISPACE;
class GameObject
{
private:
protected:
	BYTE* m_frame{ nullptr };
	int m_health{999};
	bool m_collected{ false };
	bool m_alive{false};
	bool m_down = false;
	int m_side{0};
	int m_type{0};
	std::pair<float, float> m_Coords;
	int tw{0}, th{0};
public:
	virtual void Move(float x,float y);
	int GetHealth();
	bool GetDown();
	void SetDown();
	virtual ~GameObject() = default;
	void Dead();
	bool ReturnAlive();
	void SetHealth(int health);
	int ReturnWidth();
	int ReturnHeight();
	bool IsCollected();
	void virtual Update(std::vector<GameObject*> Entities) = 0;
	void virtual Spawn(std::string frame, std::pair<float, float> Coords, int range, int firerate, int towerType, std::pair<float, float> enemyCoords);
	void virtual Ressurect(int health, bool respawn, int armour, float speed, int level, std::string frame, std::pair<float, float> Coords, bool alive);
	int GetSide();
	BYTE* GetImage();
	std::pair<float, float> GetPosition();
	void SetPosition(std::pair<float, float> set);
	int virtual GetType() = 0;
};