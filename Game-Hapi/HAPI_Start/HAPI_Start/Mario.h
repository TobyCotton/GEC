#pragma once
#include "GameObject.h"

class Mario:public GameObject
{
private:
	std::pair<float, float> change{0,0};
	std::pair<int, int> m_flag{ 0,0 };
	int counter{ 0 };
	int animationCount{ 0 };
	int direction{ 0 };
	std::vector<BYTE*> left;
	std::vector<BYTE*> right;
public:
	Mario(int X, int Y);
	~Mario();
	void Normalise();
	BYTE* GetImage() override;
	void FlagChanger(std::pair<int, int> flag);
	void Update() override;
	std::pair<float,float> GetPosition() override;
	void SetPosition(std::pair<float, float> set) override;
};