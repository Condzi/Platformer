#pragma once
#include "CollisionSides.hpp"

struct CollisionInfo
{
	CollisionSide side;
	size_t id;

	CollisionInfo(CollisionSide side = none, size_t id = 0)
	{
		this->side = side;
		this->id = id;
	}

	bool operator==(const CollisionInfo & a)
	{
		return (a.side == side && a.id == id) ? true : false;
	}

	bool operator!=(const CollisionInfo & a)
	{
		return(operator==(a)) ? false : true;
	}
};