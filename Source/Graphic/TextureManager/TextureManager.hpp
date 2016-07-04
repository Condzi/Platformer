#pragma once
#include "..\TextureFixed.hpp"

class TextureManager
{
private:
	bool loadFromFile(const std::string & filePath);

public:
	TextureManager();
	~TextureManager();

	void SetTexturesPaths(const std::vector<std::string> & path);
	bool AddPath(const std::string & path);
	bool DelPath(const std::string & path);

	void ReloadTextures();

	const TextureFixed * GetTexture(const std::string & tag);
	const TextureFixed * GetTexture(const size_t & id);
	///	Call it in destructor of class that use reference of texture
	void GiveBackTexture(TextureFixed * texture);

private:
	std::vector<TextureFixed*> m_textures;
};

