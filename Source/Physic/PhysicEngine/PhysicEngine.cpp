#include "PhysicEngine.hpp"


void PhysicEngine::calculateCollisionPoints(const BoxCollider & b, sf::Vector2f points[8])
{
	//I make them to be variables so processor calculate it once
	float widthAndLeft = b.x + b.sizeX;
	float halfWidthAndLeft = b.x + (b.sizeX / 2);
	float heightAndTop = b.y + b.sizeY;
	float halfHeightAndTop = b.y + (b.sizeY / 2);
	
	points[0].x = b.x;
	points[0].y = b.y;
	
	points[1].x = halfWidthAndLeft;
	points[1].y = b.y;
	
	points[2].x = widthAndLeft;
	points[2].y = b.y;
	
	points[3].x = widthAndLeft;
	points[3].y = halfHeightAndTop;
	
	points[4].x = widthAndLeft;
	points[4].y = heightAndTop;
	
	points[5].x = halfWidthAndLeft;
	points[5].y = heightAndTop;
	
	points[6].x = b.x;
	points[6].y = heightAndTop;
	
	points[7].x = b.x;
	points[7].y = halfHeightAndTop;
}

float PhysicEngine::calculatePointsDistance(sf::Vector2f & p1, sf::Vector2f & p2) const
{
	//--Polish Comments For Me Zone-- \
		Wzor: \
		pierwiastek_kwadratowy(kwadrat(x2 - x1) + kwadrat(y2 - y2)) \
	//----
	return static_cast<float>(sqrt(pow(static_cast<int>((abs(p2.x) - abs(p1.x))), 2) + pow(static_cast<int>((abs(p2.y) - abs(p1.y))), 2)));
}

CollisionSide PhysicEngine::checkCollisionSide(const BoxCollider & a, const BoxCollider & b)
{
	if (!checkSimplyCollision(a, b))
		return CollisionSide::none;

	//--Polish Comments For Me Zone-- \
		Obliczanie kolizji odbywa sie w ten sposob, ze wyliczam \
		srodek prostokata 'a' i obliczam odleglosc do naroznikow i bokow \
		prostokata 'b'. Kolizja moze byc z 8 punktami, rozmieszczonymi na prostokacie 'b'. \
	//----
	
	sf::Vector2f collisionPoints[8];
	sf::Vector2f middleOfA = sf::Vector2f(a.x + a.sizeX / 2, a.y + a.sizeY / 2);
	sf::Vector2u smallestDistance(0,0);
	float distances[8];
	//distace, id
	
	calculateCollisionPoints(b, collisionPoints);
	
	for (uint8_t i = 0; i < 8; ++i)
	{
		distances[i] = calculatePointsDistance(middleOfA, collisionPoints[i]);	
	}
	smallestDistance.x = distances[0];
	smallestDistance.y = 0;

	for (uint8_t i = 0; i < 8; ++i)
	{
		if (distances[i] < smallestDistance.x)
		{
			smallestDistance.x = distances[i];
			smallestDistance.y = i;
		}
	}

	return CollisionSide(smallestDistance.y);
}

bool PhysicEngine::checkSimplyCollision(const BoxCollider & a, const BoxCollider & b) 
{
	return (a.x + a.sizeX > b.x &&
		a.x < b.x + b.sizeX &&
		a.y + a.sizeY > b.y &&
		a.y < b.y + b.sizeY)
		? true : false;
}

void PhysicEngine::updateCollisions()
{
	//I think it's the most inefficient way I can imagine, but hey!
	//It works!
	for (BoxCollider * var1 : m_colliders)
	{
		for (BoxCollider * var2 : m_colliders)
		{
			if (var1 == nullptr || var2 == nullptr)
				continue;
			if (var1 == var2)
				continue;
			
			if (checkSimplyCollision(*var1, *var2))
			{
				var1->addCollisionInfo(CollisionInfo(Simple, var2->m_physicEngineID));
				var2->addCollisionInfo(CollisionInfo(Simple, var1->m_physicEngineID));

				if (!var1->checkSimplyCollision)
					var1->addCollisionInfo(CollisionInfo(checkCollisionSide(*var1, *var2), var2->m_physicEngineID));
				
				if (!var2->checkSimplyCollision)
					var2->addCollisionInfo(CollisionInfo(checkCollisionSide(*var2, *var1), var1->m_physicEngineID));
			}
		}
	}
}

void PhysicEngine::updateRigidbodies(const float & deltaTime)
{
	for (Rigidbody * r : m_rigidbodies)
	{
		r->positionX += r->positionX * r->velocityX / r->dragX * deltaTime;
		if (r->applyGravity)
		{
			r->velocityY += r->gravity * r->mass;
		}
		r->positionY += r->positionY * r->velocityY / r->dragY * deltaTime;
	}
}

void PhysicEngine::deleteCollidersAndRigidbodies()
{
	for (BoxCollider * var : m_colliders)
	{
		if (var != nullptr)
		{
			delete var;
			var = nullptr;
		}
	}

	for (Rigidbody * var : m_rigidbodies)
	{
		if (var != nullptr)
		{
			delete var;
			var = nullptr;
		}
	}
}


PhysicEngine::PhysicEngine()
{
	m_currentIDcounter = 0;
}


PhysicEngine::~PhysicEngine()
{
	deleteCollidersAndRigidbodies();
}

size_t PhysicEngine::GetCollidersCount()
{
	return m_colliders.size();
}

size_t PhysicEngine::GetRigidbodiesCount()
{
	return m_rigidbodies.size();
}

size_t PhysicEngine::GetID()
{
	return m_currentIDcounter;
}

bool PhysicEngine::AddCollider(const BoxCollider & collider)
{
	for (BoxCollider * var : m_colliders)
		if (*var == collider)
			return false;

	if (m_colliders.size() + 1 > m_colliders.max_size())
		return false;

	m_colliders.push_back(new BoxCollider(collider));
	m_colliders[m_colliders.size()-1]->m_physicEngineID = ++m_currentIDcounter;
	return true;
}

bool PhysicEngine::AddRigidbody(const Rigidbody & rigidbody)
{
	for (Rigidbody * var : m_rigidbodies)
		if (*var == rigidbody)
			return false;

	if (m_rigidbodies.size() + 1 > m_rigidbodies.max_size())
		return false;

	m_rigidbodies.push_back(new Rigidbody(rigidbody));
	m_rigidbodies[m_rigidbodies.size()-1]->m_physicEngineID = ++m_currentIDcounter;
	return true;
}

bool PhysicEngine::DelCollider(const size_t & id)
{
	if (id > m_currentIDcounter)
		return false;

	for (BoxCollider * var : m_colliders)
	{
		if (var->m_physicEngineID == id)
		{
			delete var;
			var = nullptr;
			return true;
		}
	}

	return false;
}

bool PhysicEngine::DelRigidbody(const size_t & id)
{
	if (id > m_currentIDcounter)
		return false;

	for (Rigidbody * var : m_rigidbodies)
	{
		if (var->m_physicEngineID == id)
		{
			delete var;
			var = nullptr;
			return true;
		}
	}

	return false;
}

void PhysicEngine::DeleteAll()
{
	deleteCollidersAndRigidbodies();

	m_colliders.resize(0);
	m_rigidbodies.resize(0);
	m_currentIDcounter = 0;
}

void PhysicEngine::Update(const float & deltaTime)
{
	for (BoxCollider * var : m_colliders)
	{
		if (var->m_wishDelete)
		{
			delete var;
			var = nullptr;
		}
	}

	for (Rigidbody * var : m_rigidbodies)
	{
		if (var->m_wishDelete)
		{
			delete var;
			var = nullptr;
		}
	}

	updateCollisions();
	updateRigidbodies(deltaTime);
}
