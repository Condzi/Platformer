#include "Rigidbody.h"



Rigidbody::Rigidbody()
{
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::Update(const float & deltaTime)
{
	positionX += positionX * velocityX * deltaTime;
	if (applyGravity)
	{
		velocityY += gravity;
	}
	positionY += positionY * velocityY * deltaTime;;

	velocityX -= dragX;
	velocityY -= dragY;
}

size_t Rigidbody::GetPhysicEngineID()
{
	return m_physicEngineID;
}

