#include "Rigidbody.hpp"


Rigidbody::Rigidbody()
{
	wishDelete = false;

	positionX = 0;
	positionY = 0;
	velocityX = 0;
	velocityY = 0;
}


Rigidbody::~Rigidbody()
{
}

size_t Rigidbody::GetPhysicEngineID()
{
	return m_physicEngineID;
}

bool Rigidbody::operator==(const Rigidbody & a)
{
	return (a.positionX == positionX &&
		a.positionY == positionY &&
		a.velocityX == velocityX &&
		a.velocityY == velocityY)
		? true : false;
}

bool Rigidbody::operator!=(const Rigidbody & a)
{
	return (operator==(a)) ? false : true;
}

