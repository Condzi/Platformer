#pragma once
#include <SFML\Graphics.hpp>

#include "..\Colliders\BoxCollider.hpp"
#include "..\Rigidbody\Rigidbody.hpp"
#include "..\CollisionSides.hpp"


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
	///	Updates Rigidbody movement for all Rigidobodies
	void updateRigidbodies(const float & deltaTime);
	/// Deletes Colliders and Rigidbodies
	void deleteCollidersAndRigidbodies();

public:
	PhysicEngine();
	~PhysicEngine();

	/// Returns Colliders count
	size_t GetCollidersCount();
	/// Returns Rigidbodies count
	size_t GetRigidbodiesCount();
	/// Returns current ID
	size_t GetID();

	/// Returns false if couldn't add Collider
	bool AddCollider(const BoxCollider & collider);
	/// Returns false if couldn't add Rigidbody
	bool AddRigidbody(const Rigidbody & rigidbody);
	/// Returns false if couldn't delete Collider
	bool DelCollider(const size_t & id);
	/// Returns false if couldn't delete Rigidbody
	bool DelRigidbody(const size_t & id);
	///	Deletes everything and resets counter \
		Good for cleanup before next-scene objects are adding Colliders and Rigidbodies
	void DeleteAll();

	///	Updates engine, called once per loop circuit
	void Update(const float & deltaTime);

private:
	std::vector<BoxCollider*> m_colliders;
	std::vector<Rigidbody*> m_rigidbodies;
	size_t m_currentIDcounter;

};

