#pragma once
#include "GameObject.h"
class Play :
    public GameObject
{
public:
    void Update(std::vector<GameObject*> Entities) override;
    Play();
    int ReturnWidth();
    int ReturnHeight();
    BYTE* GetImage();
    std::pair<float, float> GetPosition();
    int GetType() override;
};

