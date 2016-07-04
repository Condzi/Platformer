#include "TextureFixed.hpp"


TextureFixed::TextureFixed(std::string tag)
{
	m_textureManagerID = 0;
	this->tag = tag;
}


TextureFixed::~TextureFixed()
{
}

size_t TextureFixed::GetTextureManagerID()
{
	return m_textureManagerID;
}

