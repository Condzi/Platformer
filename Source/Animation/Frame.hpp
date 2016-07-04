#pragma once
#include "..\Graphic\TextureFixed.hpp"
#include "CutValues.hpp"

class Frame
{
public:
	Frame();
	~Frame();

	///	Frame display time in seconds
	float duration;
	CutValues cutValues;
	sf::Texture
};



