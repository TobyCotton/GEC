#include "Mario.h"

Mario::Mario(int X, int Y)
{
	for (int i = 0; i < 6; i++)
	{
		if (!HAPI.LoadTexture("Data\\StickMan\\runL-" + std::to_string(i) + ".png", &frame, tw, th))// Loading all textures from file for left animation
		{
			HAPI.UserMessage("Missing left Sprite texture", "Error");
			HAPI.Close();
		}
		left.push_back(frame);
		if (!HAPI.LoadTexture("Data\\StickMan\\runR-" + std::to_string(i) + ".png", &frame, tw, th))// Loading all textures from file for right animation
		{
			HAPI.UserMessage("Missing right Sprite texture", "Error");
			HAPI.Close();
		}
		right.push_back(frame);
	}
	Coords.first = X;
	Coords.second = Y;
}

Mario::~Mario()// preventing memory leaks from this class
{
	delete frame;
}

void Mario::Normalise()// Normalising the movement so it is not faster to go in a diagonal motion due to pythagoras
{
	float value = sqrt(pow(change.first, 2) + pow(change.second, 2));
	if (value != 0)
	{
		change.first = change.first / value;
		change.second = change.second / value;
		Coords.first += round(change.first*4);
		Coords.second += round(change.second*4);
	}
	change.first = 0;
	change.second = 0;
	
}

BYTE* Mario::GetImage()//Getting image for viszualization class
{
	if (direction == 1)
	{
		return right[animationCount];
	}
	else
	{
		return left[animationCount];
	}
}

void Mario::FlagChanger(std::pair<int, int> flag)//for update function
{
	m_flag = flag;
}

void Mario::Update()//Updates character position direction and animation count
{
	if (m_flag.first == 1)
	{
		change.first--;
	}
	if (m_flag.first == 2)
	{
		change.first++;
	}
	if (m_flag.second == 1)
	{
		change.second--;
	}
	if (m_flag.second == 2)
	{
		change.second++;
	}
	counter++;
	if (direction == 0 && m_flag.first==1)
	{
		if (counter == 10)
		{
			if (animationCount < 5)
				animationCount++;
			else
				animationCount = 0;
			counter = 0;
		}
	}
	else if (direction== 1 && m_flag.first ==1)
	{
		direction = 0;
		animationCount = 0;
		counter = 0;
	}
	else if (direction == 1 && m_flag.first ==2)
	{
		if (counter == 10)
		{
			if (animationCount < 5)
				animationCount++;
			else
				animationCount = 0;
			counter = 0;
		}
	}
	else if (direction==0 && m_flag.first == 2)
	{
		direction = 1;
		animationCount = 0;
		counter = 0;
	}
}

std::pair<float, float> Mario::GetPosition()
{
	return Coords;
}

void Mario::SetPosition(std::pair<float,float> set)
{
	Coords.first = set.first;
	Coords.second = set.second;
}
