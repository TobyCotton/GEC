#include "Graphics.h"

Graphics::Graphics()
{
	if (!HAPI.Initialise(m_width, m_height))
		return;
	m_Screen = HAPI.GetScreenPointer();
	HAPI.SetShowFPS(true, 0, 0, HAPI_TColour::WHITE);
}

void Graphics::SetScreenColour(HAPI_TColour colour)// Clearing screen for redraw
{
	int pixel{ 0 };
	for (int i = 0; i < m_width * m_height; i++)
	{
		m_Screen[pixel] = colour.red;
		m_Screen[pixel + 1] = colour.green;
		m_Screen[pixel + 2] = colour.blue;
		m_Screen[pixel + 3] = colour.alpha;
		pixel += 4;
	}
}

void Graphics::Render(BYTE* image, std::pair<float, float> Coords,int th,int tw)//Normal render function
{
	int offset{ 0 };
	int texptr{ 0 };
	offset = (Coords.second * m_width * 4) + (Coords.first * 4);
	for (int y = 0; y < th; y++)
	{
		for (int x = 0; x < tw; x++)
		{
			if (image[texptr + 3] == 255)
			{
				m_Screen[offset] = image[texptr];
				m_Screen[offset + 1] = image[texptr + 1];
				m_Screen[offset + 2] = image[texptr + 2];
				m_Screen[offset + 3] = image[texptr + 3];
			}
			else if (image[texptr + 3] == 0);
			else
			{
				float mix = image[texptr + 3] / 255.0f;
				m_Screen[offset] = (image[texptr] * mix) + (m_Screen[offset] * (1 - mix));
				m_Screen[offset + 1] = (image[texptr + 1] * mix) + (m_Screen[offset + 1] * (1 - mix));
				m_Screen[offset + 2] = (image[texptr + 2] * mix) + (m_Screen[offset + 2] * (1 - mix));
				m_Screen[offset + 3] = (image[texptr + 3] * mix) + (m_Screen[offset + 3] * (1 - mix));
			}
			offset += 4;
			texptr += 4;
		}
		offset += (m_width - tw) * 4;
	}
}

void Graphics::RenderClip(int flagX, int flagY, std::pair<float, float> Coords, BYTE* image, int th, int tw)//Clipping code
{
	int offset{ 0 };
	int Xoff{ 0 };
	int Yoff{ 0 };
	int texptr{ 0 };
	if (flagX == 1)
	{
		if (flagY == 1)
		{
			offset = (Coords.second * m_width * 4) + (Coords.first * 4);
			Xoff = 64 - (m_width - Coords.first);
			Yoff = 64 - (m_height - Coords.second);
			if (Xoff < 0 || Yoff < 0)
			{
				Xoff = 0;
				Yoff = 0;
			}
			for (int y = 0; y < th - Yoff; y++)
			{
				for (int x = 0; x < tw - Xoff; x++)
				{
					if (image[texptr + 3] == 255)
					{
						m_Screen[offset] = image[texptr];
						m_Screen[offset + 1] = image[texptr + 1];
						m_Screen[offset + 2] = image[texptr + 2];
						m_Screen[offset + 3] = image[texptr + 3];
					}
					else if (image[texptr + 3] == 0);
					else
					{
						float mix = image[texptr + 3] / 255.0f;
						m_Screen[offset] = (image[texptr] * mix) + (m_Screen[offset] * (1 - mix));
						m_Screen[offset + 1] = (image[texptr + 1] * mix) + (m_Screen[offset + 1] * (1 - mix));
						m_Screen[offset + 2] = (image[texptr + 2] * mix) + (m_Screen[offset + 2] * (1 - mix));
						m_Screen[offset + 3] = (image[texptr + 3] * mix) + (m_Screen[offset + 3] * (1 - mix));
					}
					offset += 4;
					texptr += 4;
				}
				offset += (m_width - (m_width - Coords.first)) * 4;
				texptr += Xoff * 4;
			}
		}
		else if (flagY == 0)
		{
			offset = (Coords.second * m_width * 4) + (Coords.first * 4);
			Xoff = 64 - (m_width - Coords.first);
			if (Xoff < 0 || Yoff < 0)
			{
				Xoff = 0;
				Yoff = 0;
			}
			for (int y = 0; y < th; y++)
			{
				for (int x = 0; x < tw - Xoff; x++)
				{
					if (image[texptr + 3] == 255)
					{
						m_Screen[offset] = image[texptr];
						m_Screen[offset + 1] = image[texptr + 1];
						m_Screen[offset + 2] = image[texptr + 2];
						m_Screen[offset + 3] = image[texptr + 3];
					}
					else if (image[texptr + 3] == 0);
					else
					{
						float mix = image[texptr + 3] / 255.0f;
						m_Screen[offset] = (image[texptr] * mix) + (m_Screen[offset] * (1 - mix));
						m_Screen[offset + 1] = (image[texptr + 1] * mix) + (m_Screen[offset + 1] * (1 - mix));
						m_Screen[offset + 2] = (image[texptr + 2] * mix) + (m_Screen[offset + 2] * (1 - mix));
						m_Screen[offset + 3] = (image[texptr + 3] * mix) + (m_Screen[offset + 3] * (1 - mix));
					}
					offset += 4;
					texptr += 4;
				}
				offset += (m_width - (m_width - Coords.first)) * 4;
				texptr += Xoff * 4;
			}
		}
		else
		{
			offset = Coords.first * 4;
			Xoff = 64 - (m_width - Coords.first);
			Yoff = 64 + Coords.second;
			texptr = (tw * 4) * (64 - Yoff);
			if (Xoff < 0 || Yoff < 0)
			{
				Xoff = 0;
				Yoff = 0;
			}
			for (int y = 0; y < Yoff; y++)
			{
				for (int x = 0; x < tw - Xoff; x++)
				{
					if (image[texptr + 3] == 255)
					{
						m_Screen[offset] = image[texptr];
						m_Screen[offset + 1] = image[texptr + 1];
						m_Screen[offset + 2] = image[texptr + 2];
						m_Screen[offset + 3] = image[texptr + 3];
					}
					else if (image[texptr + 3] == 0);
					else
					{
						float mix = image[texptr + 3] / 255.0f;
						m_Screen[offset] = (image[texptr] * mix) + (m_Screen[offset] * (1 - mix));
						m_Screen[offset + 1] = (image[texptr + 1] * mix) + (m_Screen[offset + 1] * (1 - mix));
						m_Screen[offset + 2] = (image[texptr + 2] * mix) + (m_Screen[offset + 2] * (1 - mix));
						m_Screen[offset + 3] = (image[texptr + 3] * mix) + (m_Screen[offset + 3] * (1 - mix));
					}
					offset += 4;
					texptr += 4;
				}
				offset += (m_width - (m_width - Coords.first)) * 4;
				texptr += Xoff * 4;
			}
		}
	}
	else if (flagX == -1)
	{
		if (flagY == -1)
		{
			offset = 0;
			Xoff = 64 + Coords.first;
			Yoff = 64 + Coords.second;
			texptr = ((tw * (th - Yoff)) * 4) + ((tw - Xoff) * 4);
			if (Xoff < 0 || Yoff < 0)
			{
				Xoff = 0;
				Yoff = 0;
			}
			for (int y = 0; y < Yoff; y++)
			{
				for (int x = 0; x < Xoff; x++)
				{
					if (image[texptr + 3] == 255)
					{
						m_Screen[offset] = image[texptr];
						m_Screen[offset + 1] = image[texptr + 1];
						m_Screen[offset + 2] = image[texptr + 2];
						m_Screen[offset + 3] = image[texptr + 3];
					}
					else if (image[texptr + 3] == 0);
					else
					{
						float mix = image[texptr + 3] / 255.0f;
						m_Screen[offset] = (image[texptr] * mix) + (m_Screen[offset] * (1 - mix));
						m_Screen[offset + 1] = (image[texptr + 1] * mix) + (m_Screen[offset + 1] * (1 - mix));
						m_Screen[offset + 2] = (image[texptr + 2] * mix) + (m_Screen[offset + 2] * (1 - mix));
						m_Screen[offset + 3] = (image[texptr + 3] * mix) + (m_Screen[offset + 3] * (1 - mix));
					}
					offset += 4;
					texptr += 4;
				}
				offset += (m_width - Xoff) * 4;
				texptr += (64 - Xoff) * 4;
			}
		}
		else if (flagY == 0)
		{
			offset = (Coords.second * m_width * 4);
			Xoff = 64 + Coords.first;
			texptr = (tw - Xoff) * 4;
			if (Xoff < 0 || Yoff < 0)
			{
				Xoff = 0;
				Yoff = 0;
			}
			for (int y = 0; y < th; y++)
			{
				for (int x = 0; x < Xoff; x++)
				{
					if (image[texptr + 3] == 255)
					{
						m_Screen[offset] = image[texptr];
						m_Screen[offset + 1] = image[texptr + 1];
						m_Screen[offset + 2] = image[texptr + 2];
						m_Screen[offset + 3] = image[texptr + 3];
					}
					else if (image[texptr + 3] == 0);
					else
					{
						float mix = image[texptr + 3] / 255.0f;
						m_Screen[offset] = (image[texptr] * mix) + (m_Screen[offset] * (1 - mix));
						m_Screen[offset + 1] = (image[texptr + 1] * mix) + (m_Screen[offset + 1] * (1 - mix));
						m_Screen[offset + 2] = (image[texptr + 2] * mix) + (m_Screen[offset + 2] * (1 - mix));
						m_Screen[offset + 3] = (image[texptr + 3] * mix) + (m_Screen[offset + 3] * (1 - mix));
					}
					offset += 4;
					texptr += 4;
				}
				offset += (m_width - Xoff) * 4;
				texptr += (64 - Xoff) * 4;
			}
		}
		else
		{
			offset = m_width * Coords.second * 4;
			Xoff = 64 + Coords.first;
			Yoff = 64 - (m_height - Coords.second);
			texptr = (tw - Xoff) * 4;
			if (Xoff < 0 || Yoff < 0)
			{
				Xoff = 0;
				Yoff = 0;
			}
			for (int y = 0; y < th - Yoff; y++)
			{
				for (int x = 0; x < Xoff; x++)
				{
					if (image[texptr + 3] == 255)
					{
						m_Screen[offset] = image[texptr];
						m_Screen[offset + 1] = image[texptr + 1];
						m_Screen[offset + 2] = image[texptr + 2];
						m_Screen[offset + 3] = image[texptr + 3];
					}
					else if (image[texptr + 3] == 0);
					else
					{
						float mix = image[texptr + 3] / 255.0f;
						m_Screen[offset] = (image[texptr] * mix) + (m_Screen[offset] * (1 - mix));
						m_Screen[offset + 1] = (image[texptr + 1] * mix) + (m_Screen[offset + 1] * (1 - mix));
						m_Screen[offset + 2] = (image[texptr + 2] * mix) + (m_Screen[offset + 2] * (1 - mix));
						m_Screen[offset + 3] = (image[texptr + 3] * mix) + (m_Screen[offset + 3] * (1 - mix));
					}
					offset += 4;
					texptr += 4;
				}
				offset += (m_width - Xoff) * 4;
				texptr += (tw - Xoff) * 4;
			}
		}
	}
	else if (flagY == -1)
	{
		offset = Coords.first * 4;
		Yoff = 64 + Coords.second;
		texptr = (tw * (th - Yoff)) * 4;
		if (Xoff < 0 || Yoff < 0)
		{
			Xoff = 0;
			Yoff = 0;
		}
		for (int y = 0; y < Yoff; y++)
		{
			for (int x = 0; x < tw; x++)
			{
				if (image[texptr + 3] == 255)
				{
					m_Screen[offset] = image[texptr];
					m_Screen[offset + 1] = image[texptr + 1];
					m_Screen[offset + 2] = image[texptr + 2];
					m_Screen[offset + 3] = image[texptr + 3];
				}
				else if (image[texptr + 3] == 0);
				else
				{
					float mix = image[texptr + 3] / 255.0f;
					m_Screen[offset] = (image[texptr] * mix) + (m_Screen[offset] * (1 - mix));
					m_Screen[offset + 1] = (image[texptr + 1] * mix) + (m_Screen[offset + 1] * (1 - mix));
					m_Screen[offset + 2] = (image[texptr + 2] * mix) + (m_Screen[offset + 2] * (1 - mix));
					m_Screen[offset + 3] = (image[texptr + 3] * mix) + (m_Screen[offset + 3] * (1 - mix));
				}
				offset += 4;
				texptr += 4;
			}
			offset += (m_width - tw) * 4;
		}
	}
	else if (flagY == 1)
	{
		offset = (Coords.second * m_width * 4) + (Coords.first * 4);
		Yoff = 64 - (m_height - Coords.second);
		if (Xoff < 0 || Yoff < 0)
		{
			Xoff = 0;
			Yoff = 0;
		}
		for (int y = 0; y < th - Yoff; y++)
		{
			for (int x = 0; x < tw; x++)
			{
				if (image[texptr + 3] == 255)
				{
					m_Screen[offset] = image[texptr];
					m_Screen[offset + 1] = image[texptr + 1];
					m_Screen[offset + 2] = image[texptr + 2];
					m_Screen[offset + 3] = image[texptr + 3];
				}
				else if (image[texptr + 3] == 0);
				else
				{
					float mix = image[texptr + 3] / 255.0f;
					m_Screen[offset] = (image[texptr] * mix) + (m_Screen[offset] * (1 - mix));
					m_Screen[offset + 1] = (image[texptr + 1] * mix) + (m_Screen[offset + 1] * (1 - mix));
					m_Screen[offset + 2] = (image[texptr + 2] * mix) + (m_Screen[offset + 2] * (1 - mix));
					m_Screen[offset + 3] = (image[texptr + 3] * mix) + (m_Screen[offset + 3] * (1 - mix));
				}
				offset += 4;
				texptr += 4;
			}
			offset += (m_width - tw) * 4;
		}
	}
}

std::pair<int, int> Graphics::ClipCheck(GameObject* object)
{
	std::pair<int, int> Flags{};
	if (object->GetPosition().first < 0)
	{
		Flags.first = -1;
	}
	if (object->GetPosition().first > m_width - 64)
	{
		Flags.first = 1;
	}
	if (object->GetPosition().second < 0)
	{
		Flags.second = -1;
	}
	if (object->GetPosition().second > m_height - 64)
	{
		Flags.second = 1;
	}
	return Flags;
}
