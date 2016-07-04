#pragma once
#include <SFML\Graphics.hpp>


class TextureFixed :
	public sf::Texture
{
	friend class TextureManager;

public:
	TextureFixed(std::string tag = "");
	~TextureFixed();
	
	/// Returns value used by Texture Manager to identyfy this texture
	size_t GetTextureManagerID();

private:
	size_t m_textureManagerID;
	bool m_wishDelete;

public:
	std::string tag;
};

