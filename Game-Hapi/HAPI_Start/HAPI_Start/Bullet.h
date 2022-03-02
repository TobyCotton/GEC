#pragma once
#include "GameObject.h"
class Bullet ://Is not used hopefully something to add in the future
    public GameObject
{
private:
    int m_piercing{};
    int m_tower{};
    std::pair<float, float> m_velocity{};
    std::pair<float, float> m_destination{};
public:
    void Update(std::vector<GameObject*> Entities) override;
    Bullet(std::string frame,bool piercing,int tower, std::pair<float, float> velocity);
    int GetType() override;
    void Spawn(std::string frame, std::pair<float, float> Coords, int range, int firerate, int towerType, std::pair<float, float> enemyCoords) override;
    void Move(float x, float y) override;
};

