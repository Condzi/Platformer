#include "Player.hpp"



Player::Player()
{
	m_boxCollider = new BoxCollider(10, 10, 100, 100);
	m_rigidbody = new Rigidbody();
	m_animationSheet = nullptr;
}


Player::~Player()
{
	if (m_animationSheet != nullptr && m_textureManager != nullptr)
		const_cast<TextureManager*>(m_textureManager)->GiveBackTexture(m_animationSheet);
}

void Player::Update()
{
	if (m_rigidbody->velocityX != 0)
		m_rigidbody->velocityX = 0;
	if (m_rigidbody->velocityY != 0)
		m_rigidbody->velocityY = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		m_rigidbody->velocityY -= 50;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		m_rigidbody->velocityY += 50;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		m_rigidbody->velocityX -= 50;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		m_rigidbody->velocityX += 50;
	GameObject::Update();

	GameObject::SetTexture(const_cast<TextureManager*>(m_textureManager)->GetTexture(m_animator.GetCurrentFrameTextureTag()));
}

bool Player::SetAnimationSheet(const TextureFixed * texture)
{
	if (texture == nullptr)
		return false;
	m_animationSheet = texture;

	m_animator.AddFrame(Frame(m_animationSheet, CutValues(0, 0, 64, 64), 0.2f, m_textureManager));
	m_animator.AddFrame(Frame(m_animationSheet, CutValues(65, 0, 64, 64), 0.2f, m_textureManager));
	m_animator.AddFrame(Frame(m_animationSheet, CutValues(129, 0, 64, 64), 0.2f, m_textureManager));

	m_animator.SetRepeat(true);
	m_animator.Start();
	m_animator.Update();
	return true;

}
