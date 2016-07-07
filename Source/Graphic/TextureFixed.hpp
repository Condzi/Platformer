#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>


class TextureFixed :
	public sf::Texture
{
	friend class TextureManager;

private:
	/// Used to update ReferenceCounter by TextureManager (if 0 then wishDelete)
	void updateReference();

public:
	TextureFixed(std::string tag = "");
	~TextureFixed();
	
	/// Returns value used by Texture Manager to identyfy this texture
	size_t GetTextureManagerID();

	bool operator==(const TextureFixed & a);
	bool operator!=(const TextureFixed & a);

private:
	size_t m_textureManagerID;
	uint16_t m_referenceCounter;
	bool m_wishDelete;

public:
	/// Better don't change that
	std::string tag;
};

