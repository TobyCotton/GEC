#pragma once
#include <HAPI_lib.h>
#include <iostream>

using namespace HAPISPACE;
class GameObject
{
private:
protected:
	std::pair<float, float> Coords;
	int tw, th;
public:
	virtual BYTE* GetImage()=0;
	virtual void Update() = 0;
	virtual std::pair<float, float> GetPosition() = 0;
	virtual void SetPosition(std::pair<float, float> set) = 0;
};

