#pragma once
#include <HAPI_lib.h>
#include "GameObject.h"
using namespace HAPISPACE;


class Graphics
{
private:
	int m_width{ 1080 };
	int m_height{ 720 };
	BYTE* m_Screen{};
	BYTE* m_image{ nullptr };
	int m_offset{ 0 };
	int m_texptr{ 0 };
public:
	int GetScreenWidth() const { return m_width; };
	int GetScreenHeight() const { return m_height; };

	Graphics();
	void Render(BYTE* image, std::pair<float, float> Coords, int th, int tw);
	void RenderClip(int flagX, int flagY, std::pair<float, float> Coords, BYTE* image, int th, int tw);
	std::pair<int, int> ClipCheck(GameObject* object);
};