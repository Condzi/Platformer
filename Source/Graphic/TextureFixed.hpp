#pragma once
#include <SFML\Graphics.hpp>


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

	bool operator==(const TextureFixed & t);

private:
	size_t m_textureManagerID;
	uint16_t m_referenceCounter;
	bool m_wishDelete;

public:
	std::string tag;
};

