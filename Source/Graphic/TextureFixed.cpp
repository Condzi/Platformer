#include "TextureFixed.hpp"


TextureFixed::TextureFixed(std::string tag)
{
	m_textureManagerID = 0;
	m_referenceCounter = 0;
	this->tag = tag;
}


TextureFixed::~TextureFixed()
{
}

size_t TextureFixed::GetTextureManagerID()
{
	return m_textureManagerID;
}

void TextureFixed::updateReference()
{
	if (m_referenceCounter == 0)
	{
		m_wishDelete = true;
	}
}

bool TextureFixed::operator==(const TextureFixed & t)
{
	return (m_textureManagerID == t.m_textureManagerID &&
		tag == t.tag)
		? true : false;
}

