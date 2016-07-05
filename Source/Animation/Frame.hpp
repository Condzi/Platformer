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
	Frame(TextureFixed * texture = nullptr, const CutValues & cutValues = CutValues(), float duration = 0.2f);
	~Frame();
	
	sf::Sprite frameSprite;
	///	Frame display time in seconds
	float duration;

	bool SetTexture(TextureFixed * texture, const CutValues & cutValues);
	bool SetTextureManagerPointer(TextureManager * textureManagerPointer);

private:
	TextureFixed * m_frameTexture;
	TextureManager * m_textureManagerPointer;

};



