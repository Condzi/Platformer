#pragma once
#include <SFML\Graphics.hpp>

#include "..\Colliders\BoxCollider.h"
#include "..\Rigidbody\Rigidbody.h"
#include "..\CollisionSides.h"


class PhysicEngine
{

private:
	///	Calculates points relative to rectangle 'b' for collision detection \
		Used only in PhysicEngine
	void calculateCollisionPoints(const BoxCollider & b, sf::Vector2f points[8]);
	/// Calculates distance between two points \
		Used only in PhysicEngine
	float calculatePointsDistance(sf::Vector2f & p1, sf::Vector2f & p2) const;
	///	Calculates and returns side of the collision for 'a' \
		Used only in PhysicEngine
	CollisionSide checkCollisionSide(const BoxCollider & a, const BoxCollider & b);
	///	Calculates simply collision - are objects overleaping?
	bool checkSimplyCollision(const BoxCollider & a, const BoxCollider & b);
	/// Updates collisions for all BoxColliders
	void updateCollisions();
	/// Deletes Colliders and Rigidbodies
	void deleteCollidersAndRigidbodies();

public:
	PhysicEngine();
	~PhysicEngine();

	/// Returns Colliders count
	size_t GetCollidersCount();
	/// Returns Rigidbodies count
	size_t GetRigidbodiesCount();
	/// Return current ID
	size_t GetID();

	bool AddCollider(BoxCollider * collider);
	bool AddRigidbody(Rigidbody * rigidbody);
	///	Deletes everything and resets counter \
		Good for cleanup before next-scene objects are adding Colliders and Rigidbodies
	void DeleteAll();

	void Update(const float & deltaTime);

private:
	std::vector<BoxCollider*> m_colliders;
	std::vector<Rigidbody*> m_rigidbodies;
	size_t m_currentIDcounter;

};

