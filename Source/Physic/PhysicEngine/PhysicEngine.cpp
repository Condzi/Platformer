#include "PhysicEngine.h"


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
	float distances[8];
	//distace, id
	sf::Vector2u smallestDistance(0,0);
	
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
	for (size_t i = 0; i < m_colliders.size(); ++i)
	{
		for (size_t j = i + 1; j < m_colliders.size(); ++j)
		{
			if (m_colliders[i] == nullptr || m_colliders[j] == nullptr)
				continue;
			if (checkCollisionSide(*m_colliders[i], *m_colliders[j]))
				m_colliders[i]->m_collisionSide = CollisionSide::Simply;
			else
				m_colliders[i]->m_collisionSide = CollisionSide::none;

			m_colliders[j]->m_collisionSide = m_colliders[i]->m_collisionSide;
		}
	}
}

void PhysicEngine::updateRigidbodies(const float & deltaTime)
{
	//I'm not sure about this...

	for each (Rigidbody * r in m_rigidbodies)
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
	for (size_t i = 0; i < m_colliders.size(); ++i)
	{
		if (m_colliders[i] != nullptr)
			delete m_colliders[i];
	}

	for (size_t i = 0; i < m_colliders.size(); ++i)
	{
		if (m_rigidbodies[i] != nullptr)
			delete m_rigidbodies[i];
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

bool PhysicEngine::AddCollider(BoxCollider * collider)
{
	if (collider == nullptr)
		return false;

	if (m_colliders.size() + 1 > std::numeric_limits<size_t>::max())
		return false;

	m_colliders.push_back(collider);
	collider->m_physicEngineID = ++m_currentIDcounter;
	return true;
}

bool PhysicEngine::AddRigidbody(Rigidbody * rigidbody)
{
	if (rigidbody == nullptr)
		return false;

	if (m_rigidbodies.size() + 1 > std::numeric_limits<size_t>::max())
		return false;

	m_rigidbodies.push_back(rigidbody);
	rigidbody->m_physicEngineID = ++m_currentIDcounter;
	return true;
}

bool PhysicEngine::DelCollider(const size_t & id)
{
	if (id > m_currentIDcounter)
		return false;

	for each (BoxCollider * var in m_colliders)
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

	for each (Rigidbody * var in m_rigidbodies)
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
	for (size_t i = 0; i < m_colliders.size(); ++i)
	{
		if (m_colliders[i]->m_wishDelete)
		{
			delete m_colliders[i];
			m_colliders[i] = nullptr;
		}
	}

	for (size_t i = 0; i < m_rigidbodies.size(); ++i)
	{
		if (m_rigidbodies[i]->m_wishDelete)
		{
			delete m_rigidbodies[i];
			m_rigidbodies[i] = nullptr;
			continue;
		}

		m_rigidbodies[i]->Update(deltaTime);
	}
}
