#pragma once
#include <cinttypes>

class Rigidbody
{
	friend class PhysicEngine;

public:
	Rigidbody();
	~Rigidbody();

	///	Returns ID used by PhysicEngine
	size_t GetPhysicEngineID();

	bool operator==(const Rigidbody & a);
	bool operator!=(const Rigidbody & a);

private:
	bool wishDelete;
	size_t m_physicEngineID;

public:
	int positionX;
	int positionY;
	int velocityX;
	int velocityY;
};

