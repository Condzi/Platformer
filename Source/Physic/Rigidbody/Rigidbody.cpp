#include "Rigidbody.hpp"


Rigidbody::Rigidbody()
{
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
		a.velocityY == velocityY &&
		a.gravity == gravity &&
		a.dragX == dragX &&
		a.dragY == dragY &&
		a.mass == mass &&
		a.applyGravity == applyGravity)
		? true : false;
}

bool Rigidbody::operator!=(const Rigidbody & a)
{
	return (operator==(a)) ? false : true;
}

