#include "TextureFixed.hpp"


TextureFixed::TextureFixed(std::string tag)
{
	m_textureManagerID = 0;
	m_referenceCounter = 0;
	this->tag = tag;
	m_wishDelete = false;
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
		std::cout << "[T] Wishing delete texture \"" << tag << "\".\n";
	}
}

bool TextureFixed::operator==(const TextureFixed & a)
{
	return (m_textureManagerID == a.m_textureManagerID &&
		tag == a.tag)
		? true : false;
}

bool TextureFixed::operator!=(const TextureFixed & a)
{
	return (operator==(a)) ? false : true;
}

