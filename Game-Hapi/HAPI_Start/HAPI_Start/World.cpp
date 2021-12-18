#include "World.h"

void World::Run()
{

	std::vector<GameObject*> Entities;
	const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();

	Mario character(512.0f, 384.0f);
	Mario character2(200.0f, 200.0f);
	Entities.push_back(&character);
	Entities.push_back(&character2);
	std::pair<int, int> flag{0,0};
	while (HAPI.Update())
	{
		flag.first = 0;
		flag.second = 0;
		const HAPI_TControllerData& ControllerData = HAPI.GetControllerData(0);
		int xFlag{};
		int yFlag{};
		int offset{ 0 };
		int texptr{ 0 };
		if (keyData.scanCode['W'] || ControllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 10000)//all input checks
		{
			flag.second = 1;
		}
		if (keyData.scanCode['S'] || ControllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -10000)
		{
			flag.second = 2;
		}
		if (keyData.scanCode['D'] || ControllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 10000)
		{
			flag.first = 2;
		}
		if (keyData.scanCode['A'] || ControllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -10000)
		{
			flag.first = 1;
		}
		character.FlagChanger(flag);
		character.Update();
		character.Normalise();

		graphicTing.SetScreenColour(HAPI_TColour::BLACK);
	
		for each (GameObject * entity in Entities)//Looping from all gameObjects
		{
			std::pair<int, int> Flags = graphicTing.ClipCheck(entity);
			if (Flags.first == 0 && Flags.second == 0)
			{
				graphicTing.Render(entity->GetImage(), entity->GetPosition(), 64, 64);
			}
			else
			{
				graphicTing.RenderClip(Flags.first, Flags.second, entity->GetPosition(), entity->GetImage(), 64, 64);
			}
		}
	}
}

