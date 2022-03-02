#pragma once
#include "GameObject.h"

class Enemy :
    public GameObject
{
private:
    std::vector<std::pair<int,int>> m_EnemyPath;
    bool m_flying{};
    int m_armour{};
    int m_level{};
    int m_direction = 0;
    float m_speed;
    int m_node=0;
public:
    void Update(std::vector<GameObject*> Entities) override;
    Enemy(int health, bool flying, int armour, float speed, int level, std::string frame, std::pair<float, float> Coords, std::vector<std::pair<int, int>> EnemyPath, bool alive);
    void Ressurect(int health, bool respawn, int armour, float speed, int level, std::string frame, std::pair<float, float> Coords,bool alive) override;
    void SetHealth(int health);
    int GetArmour();
    float GetSpeed();
    int GetLevel();
    void Move(float x,float y) override;
    int GetType() override;
};

