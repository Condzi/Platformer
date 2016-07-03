#pragma once
#include <cinttypes>

#include "..\CollisionSides.h"


class BoxCollider
{
	friend class PhysicEngine;

private:
	void modifyIsTriggered(const bool & newStatement);

public:
	BoxCollider(int32_t x = 0, int32_t y = 0, int32_t sizeX = 0, int32_t sizeY = 0, bool isTriggered = false);
	~BoxCollider();

	int32_t x;
	int32_t y;
	int32_t sizeX;
	int32_t sizeY;
	/// It's really important field so can be changed \
		Only using SetIsTriggered method
	const bool isTriggered = false;
	///	Returns collision side
	CollisionSide GetCollisionSide();
	/// Returns true if colliding
	bool GetIsColliding();
	///	Returns ID used by PhysicEngine
	size_t GetPhysicEngineID();
	///	Sets IsTriggered variable
	void SetIsTriggered(const bool & newStatement);

	bool operator==(BoxCollider & a);
	bool operator!=(BoxCollider & a);

private:
	CollisionSide m_collisionSide;
	bool m_wishDelete;
	size_t m_physicEngineID;

};

