#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

#include "..\Graphic\TextureManager\TextureManager.hpp"
#include "..\Physic\Colliders\BoxCollider.hpp"
#include "..\Physic\Rigidbody\Rigidbody.hpp"


class GameObject :
	public sf::Drawable
{
private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;

public:
	GameObject();
	~GameObject();

	void SetTexture(const TextureFixed * texture);
	void SetTextureManagerPointer(const TextureManager * textureManager);
	void SetBoxCollider(const BoxCollider & collider);
	void SetRigidbody(const Rigidbody & rigidbody);

	sf::Sprite * ChangeSpriteAttributes();

	TextureFixed GetTexture();
	BoxCollider * GetBoxCollider();
	Rigidbody * GetRigidbody();
	
	void Update();

private:
	const TextureFixed * m_texture;
	const TextureManager * m_textureManager;
	const sf::Sprite * m_sprite;

protected:
	BoxCollider * m_boxCollider;
	Rigidbody * m_rigidbody;
	
};

