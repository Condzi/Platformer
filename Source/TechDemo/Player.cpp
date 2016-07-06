#include "Player.hpp"



Player::Player()
{
	m_boxCollider = new BoxCollider(10, 10, 100, 100);
	m_rigidbody = new Rigidbody();
}


Player::~Player()
{
}

void Player::Update()
{
	if (m_rigidbody->velocityX != 0)
		m_rigidbody->velocityX = 0;
	if (m_rigidbody->velocityY != 0)
		m_rigidbody->velocityY = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		m_rigidbody->velocityY -= 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		m_rigidbody->velocityY += 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		m_rigidbody->velocityX -= 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		m_rigidbody->velocityX += 5;
	GameObject::Update();
}
