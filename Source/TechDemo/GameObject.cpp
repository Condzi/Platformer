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
	if (m_texture != nullptr && m_textureManager != nullptr)
		const_cast<TextureManager*>(m_textureManager)->GiveBackTexture(m_texture);
	if(m_sprite != nullptr)
		delete m_sprite;
	if (m_boxCollider != nullptr)
		m_boxCollider->wishDelete = true;
	if (m_rigidbody != nullptr)
		m_boxCollider->wishDelete = true;
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

void GameObject::SetBoxCollider(const BoxCollider & collider)
{
	if (m_boxCollider != nullptr)
	{
		delete m_boxCollider;
		m_boxCollider = nullptr;
		SetBoxCollider(collider);
		return;
	}

	m_boxCollider = new BoxCollider(collider);
}

void GameObject::SetRigidbody(const Rigidbody & rigidbody)
{
	if (m_rigidbody != nullptr)
	{
		delete m_rigidbody;
		m_rigidbody = nullptr;
		SetRigidbody(rigidbody);
		return;
	}

	m_rigidbody = new Rigidbody(rigidbody);
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

BoxCollider * GameObject::GetBoxCollider()
{
	return m_boxCollider;
}

Rigidbody * GameObject::GetRigidbody()
{
	return m_rigidbody;
}

void GameObject::Update()
{
	if (m_rigidbody != nullptr && m_sprite != nullptr)
	{
		ChangeSpriteAttributes()->setPosition(
			m_sprite->getPosition().x +
			(m_rigidbody->positionX != m_sprite->getPosition().x) ? m_rigidbody->positionX : 0,
			m_sprite->getPosition().y +
			(m_rigidbody->positionY != m_sprite->getPosition().y) ? m_rigidbody->positionY : 0);
		std::cout << m_sprite->getPosition().x << ", " << m_sprite->getPosition().y << " | "<<m_rigidbody->velocityX<<", "<<m_rigidbody->velocityY<<"\n";
	}

}
