#include "Frame.hpp"


void Frame::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(frameSprite, states);
}

Frame::Frame(const TextureFixed * texture, const CutValues & cutValues, float duration, const TextureManager * textureManagerPtr)
{
	SetTexture(texture, cutValues);
	this->duration = duration;
	m_textureManagerPointer = textureManagerPtr;
}

Frame::~Frame()
{
	if (m_textureManagerPointer != nullptr)
		const_cast<TextureManager*>(m_textureManagerPointer)->GiveBackTexture(m_frameTexture);
}

bool Frame::SetTexture(const TextureFixed * texture, const CutValues & cutValues)
{
	if (texture == nullptr ||
		texture == m_frameTexture)
		return false;

	frameSprite.setTexture(*texture);
	frameSprite.setTextureRect(sf::IntRect(cutValues.x, cutValues.y, cutValues.width, cutValues.height));
	
	return true;
}

bool Frame::SetTextureManagerPointer(const TextureManager * textureManagerPointer)
{
	if (textureManagerPointer == nullptr ||
		textureManagerPointer == m_textureManagerPointer)
		return false;

	m_textureManagerPointer = textureManagerPointer;
	return true;
}



