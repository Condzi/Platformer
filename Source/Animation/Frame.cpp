#include "Frame.hpp"


void Frame::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_frameSprite);
}

Frame::Frame(TextureFixed * texture, const CutValues & cutValues, float duration)
{
	SetTexture(texture, cutValues);
	this->duration = duration;
	m_textureManagerPointer = nullptr;
}

Frame::~Frame()
{
	if (m_textureManagerPointer != nullptr)
		m_textureManagerPointer->GiveBackTexture(m_frameTexture);
}

bool Frame::SetTexture(TextureFixed * texture, const CutValues & cutValues)
{
	if (texture == nullptr ||
		texture == m_frameTexture)
		return false;

	m_frameSprite.setTexture(*texture);
	m_frameSprite.setTextureRect(sf::IntRect(cutValues.x, cutValues.y, cutValues.width, cutValues.height));
	
	return true;
}

bool Frame::SetTextureManagerPointer(TextureManager * textureManagerPointer)
{
	if (textureManagerPointer == nullptr ||
		textureManagerPointer == m_textureManagerPointer)
		return false;

	m_textureManagerPointer = textureManagerPointer;
	return true;
}


