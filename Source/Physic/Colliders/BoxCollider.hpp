#pragma once
#include <cinttypes>
#include <vector>

#include "..\CollisionInfo.hpp"


class BoxCollider
{
	friend class PhysicEngine;

private:
	/// Helping methof for PhysicEngine
	bool addCollisionInfo(const CollisionInfo & collisionInfo);

public:
	BoxCollider(int32_t x = 0, int32_t y = 0, int32_t sizeX = 0, int32_t sizeY = 0, bool isTriggered = false);
	~BoxCollider();

	///	Returns collision side \
		If no collision returns:\
		CollisionSide::none, \
		id = 0
	std::vector<CollisionInfo> GetCollisionInfo();
	/// Returns true if colliding with anything
	bool GetIsColliding();
	/// Returns true if colliding with BoxCollider with specified id
	bool IsCollidingWith(const size_t & id, CollisionInfo * collInfo = nullptr);
	///	Returns ID used by PhysicEngine
	size_t GetPhysicEngineID();
	///	Sets IsTriggered variable
	void SetIsTriggered(const bool & newStatement);

	bool operator==(const BoxCollider & a);
	bool operator!=(const BoxCollider & a);

private:
	std::vector<CollisionInfo*> m_collisionInfo;
	size_t m_physicEngineID;

public:
	int32_t x;
	int32_t y;
	int32_t sizeX;
	int32_t sizeY;
	/// It's really important field so can be changed \
		Only using SetIsTriggered method
	const bool isTriggered = false;
	///	True - check simply collision (is collision or not)\
		False - check complicated (with sides)
	bool checkSimplyCollision;
	bool wishDelete;

};

