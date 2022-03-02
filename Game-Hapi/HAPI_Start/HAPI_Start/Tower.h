#pragma once
#include "GameObject.h"
class Tower :
    public GameObject
{
private:
    int m_firerate{};
    int m_upgrade = 0;
    std::vector<std::pair<float, float>> m_values{};
    int m_tick = 0;
    std::pair<float, float> m_velocity{};
    int m_towerType{};
    int m_range{};
    bool flag{ false };
public:
    Tower(std::string frame, std::pair<float, float> Coords, bool alive, int range, int firerate);
    void Spawn(std::string frame, std::pair<float, float> Coords, int range, int firerate,int towerType, std::pair<float, float> enemyCoords) override;
    void Move(float x, float y) override;
    int GetType() override;
    void Update(std::vector<GameObject*> Entities) override;
    void Shoot(std::vector<GameObject*> Entities);
};

