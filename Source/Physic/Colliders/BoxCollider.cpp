#include "BoxCollider.hpp"


bool BoxCollider::addCollisionInfo(const CollisionInfo & collisionInfo)
{
	CollisionInfo * temp = nullptr;
	IsCollidingWith(collisionInfo.id, temp);

	if (*temp == collisionInfo)
		return false;
	if (temp->id == collisionInfo.id)
		temp->side == collisionInfo.side;
		return true;
	if (collisionInfo.id == m_physicEngineID)
		return false;
	if (m_collisionInfo.size() + 1 > m_collisionInfo.max_size())
		return false;

	m_collisionInfo.push_back(new CollisionInfo(collisionInfo));

	return true;
}

BoxCollider::BoxCollider(int32_t x, int32_t y, int32_t sizeX, int32_t sizeY, bool isTriggered)
{
	this->x = x;
	this->y = y;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	SetIsTriggered(isTriggered);
}


BoxCollider::~BoxCollider()
{
	for (CollisionInfo * var : m_collisionInfo)
	{
		if (var != nullptr)
		{
			delete var;
			var = nullptr;
		}
	}
}


std::vector<CollisionInfo> BoxCollider::GetCollisionInfo()
{
	std::vector<CollisionInfo> temp;
	temp.resize(m_collisionInfo.size());

	for (size_t i = 0; i < temp.size(); ++i)
	{
		temp[i] = *m_collisionInfo[i];
	}

	return temp;
}

bool BoxCollider::GetIsColliding()
{
	for (size_t i = 0; i < m_collisionInfo.size(); ++i)
	{
		if (m_collisionInfo[i] != nullptr &&
			m_collisionInfo[i]->side != none)
		{
			return true;
		}
	}

	return false;
}

bool BoxCollider::IsCollidingWith(const size_t & id, CollisionInfo * collInfo)
{
	for (size_t i = 0; i < m_collisionInfo.size(); ++i)
	{
		if (m_collisionInfo[i] != nullptr && m_collisionInfo[i]->id == id)
		{
			collInfo = m_collisionInfo[i];
			return true;
		}
	}

	return false;
}

size_t BoxCollider::GetPhysicEngineID()
{
	return m_physicEngineID;
}

void BoxCollider::SetIsTriggered(const bool & newStatement)
{
	const_cast<bool&>(this->isTriggered) = newStatement;
}

bool BoxCollider::operator==(const BoxCollider & a)
{
	return (a.x == x &&
		a.y == y &&
		a.sizeX == sizeX &&
		a.sizeY == sizeY)
		? true : false;
}

bool BoxCollider::operator!=(const BoxCollider & a)
{
	return (operator==(a))?false:true;
}

