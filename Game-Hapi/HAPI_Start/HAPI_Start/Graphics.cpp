#include "Graphics.h"

Graphics::Graphics()
{
	if (!HAPI.Initialise(m_width, m_height))
		return;
	m_Screen = HAPI.GetScreenPointer();
	HAPI.SetShowFPS(true, 0, 0, HAPI_TColour::WHITE);
}


void Graphics::Render(BYTE* image, std::pair<float, float> Coords, int th, int tw)//Normal render function
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
	if (flagX == 1)//bottom right corner
	{
		if (flagY == 1)
		{
			offset = (Coords.second * m_width * 4) + (Coords.first * 4);
			Xoff = tw - (m_width - Coords.first);
			Yoff = th - (m_height - Coords.second);
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
		else if (flagY == 0)//right hand side of the screen
		{
			offset = (Coords.second * m_width * 4) + (Coords.first * 4);
			Xoff = tw - (m_width - Coords.first);
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
			Xoff = tw - (m_width - Coords.first);
			Yoff = th + Coords.second;
			texptr = (tw * 4) * (th - Yoff);
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
		if (flagY == -1)//top left corner
		{
			offset = 0;
			Xoff = tw + Coords.first;
			Yoff = th + Coords.second;
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
				texptr += (tw - Xoff) * 4;
			}
		}
		else if (flagY == 0)//left hand side of the screen
		{
			offset = (Coords.second * m_width * 4);
			Xoff = tw + Coords.first;
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
				texptr += (tw - Xoff) * 4;
			}
		}
		else//top right corner
		{
			offset = m_width * Coords.second * 4;
			Xoff = tw + Coords.first;
			Yoff = th - (m_height - Coords.second);
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
	else if (flagY == -1)//top side of the screen
	{
		offset = Coords.first * 4;
		Yoff = th + Coords.second;
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
	else if (flagY == 1)//bottom side of the screen
	{
		offset = (Coords.second * m_width * 4) + (Coords.first * 4);
		Yoff = th - (m_height - Coords.second);
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

std::pair<int, int> Graphics::ClipCheck(GameObject* object)//checks what side of the image is clipped
{
	std::pair<int, int> Flags{};
	if (object->GetPosition().first < 0)
	{
		Flags.first = -1;
	}
	if (object->GetPosition().first > m_width - object->ReturnWidth())
	{
		Flags.first = 1;
	}
	if (object->GetPosition().second < 0)
	{
		Flags.second = -1;
	}
	if (object->GetPosition().second > m_height - object->ReturnHeight())
	{
		Flags.second = 1;
	}
	return Flags;
}
