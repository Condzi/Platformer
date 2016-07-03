#pragma once


class Rigidbody
{
	friend class PhysicEngine;

public:
	Rigidbody();
	~Rigidbody();

	int positionX;
	int positionY;
	int velocityX;
	int velocityY;
	int gravity;
	int dragX;
	int dragY;
	unsigned short mass;
	bool applyGravity;

	///	Returns ID used by PhysicEngine
	size_t GetPhysicEngineID();

private:
	bool m_wishDelete;
	size_t m_physicEngineID;
};

