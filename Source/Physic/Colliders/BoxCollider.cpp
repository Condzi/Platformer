#include "BoxCollider.h"


void BoxCollider::modifyIsTriggered(const bool & newStatement)
{
	const_cast<bool&>(this->isTriggered) = newStatement;
}

BoxCollider::BoxCollider(int32_t x, int32_t y, int32_t sizeX, int32_t sizeY, bool isTriggered)
{
	this->x = x;
	this->y = y;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	modifyIsTriggered(isTriggered);
}

BoxCollider::~BoxCollider()
{
}

CollisionSide BoxCollider::GetCollisionSide()
{
	return m_collisionSide;
}

bool BoxCollider::GetIsColliding()
{
	return (m_collisionSide != CollisionSide::none) ? true : false;
}

size_t BoxCollider::GetPhysicEngineID()
{
	return m_physicEngineID;
}

void BoxCollider::SetIsTriggered(const bool & newStatement)
{
	modifyIsTriggered(newStatement);
}

bool BoxCollider::operator==(BoxCollider & a)
{
	return (a.x == x &&
		a.y == y &&
		a.sizeX == sizeX &&
		a.sizeY == sizeY)
		? true : false;
}

bool BoxCollider::operator!=(BoxCollider & a)
{
	return (operator==(a))?false:true;
}

