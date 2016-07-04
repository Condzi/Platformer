#pragma once
#include <cinttypes>


struct CutValues
{
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;

	CutValues(uint16_t x = 0, uint16_t y = 0, uint16_t width = 0, uint16_t height = 0)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	bool operator==(const CutValues & a)
	{
		return (x == a.x &&
			y == a.y &&
			width == a.width &&
			height == a.height)
			? true : false;
	}

	bool operator!=(const CutValues & a)
	{
		return (operator==(a)) ? false : true;
	}
};