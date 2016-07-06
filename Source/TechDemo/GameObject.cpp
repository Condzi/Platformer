#include "GameObject.hpp"


void GameObject::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_sprite != nullptr)
		target.draw(*m_sprite, states);
}

GameObject::GameObject()
{
	m_texture = nullptr;
	m_textureManager = nullptr;
	m_boxCollider = nullptr;
	m_rigidbody = nullptr;
	m_sprite = nullptr;
}


GameObject::~GameObject()
{
	const_cast<TextureManager*>(m_textureManager)->GiveBackTexture(m_texture);
	delete m_sprite;
}

void GameObject::SetTexture(const TextureFixed * texture)
{
	m_texture = texture;
	m_sprite = new sf::Sprite;
	ChangeSpriteAttributes()->setTexture(*m_texture);
}

void GameObject::SetTextureManagerPointer(const TextureManager * textureManager)
{
	m_textureManager = textureManager;
}

void GameObject::SetBoxCollider(BoxCollider * collider)
{
	m_boxCollider = collider;
}

void GameObject::SetRigidbody(Rigidbody * rigidbody)
{
	m_rigidbody = rigidbody;
}

sf::Sprite * GameObject::ChangeSpriteAttributes()
{
	if (m_sprite == nullptr)
		return nullptr;

	return const_cast<sf::Sprite*>(m_sprite);
}

TextureFixed GameObject::GetTexture()
{
	return *m_texture;
}

BoxCollider GameObject::GetBoxCollider()
{
	return *m_boxCollider;
}

Rigidbody GameObject::GetRigidbody()
{
	return *m_rigidbody;
}

void GameObject::Update()
{
	if (m_rigidbody != nullptr && m_sprite != nullptr)
		ChangeSpriteAttributes()->setPosition(m_rigidbody->positionX, m_rigidbody->positionY);
}
