#pragma once
#include "GameObject.h"
class Map :
    public GameObject
{
public:
    void Update(std::vector<GameObject*> Entities) override;
    Map();
    int ReturnWidth();
    int ReturnHeight();
    BYTE* GetImage();
    std::pair<float, float> GetPosition();
    int GetType() override;
};

