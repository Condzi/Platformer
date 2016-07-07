#pragma once
#include "..\Graphic\TextureFixed.hpp"
#include "..\Graphic\TextureManager\TextureManager.hpp"
#include "CutValues.hpp"

class Frame :
	public sf::Drawable
{
	friend class Animator;

private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;

public:
	Frame(const TextureFixed * texture = nullptr, const CutValues & cutValues = CutValues(), float duration = 0.2f, const TextureManager * textureManagerPtr = nullptr);
	~Frame();
	
	sf::Sprite frameSprite;
	///	Frame display time in seconds
	float duration;

	bool SetTexture(const TextureFixed * texture, const CutValues & cutValues);
	bool SetTextureManagerPointer(const TextureManager * textureManagerPointer);

private:
	const TextureFixed * m_frameTexture;
	const TextureManager * m_textureManagerPointer;

};



