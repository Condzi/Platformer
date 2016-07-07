#pragma once
#include "..\TextureFixed.hpp"

class TextureManager
{
private:
	bool loadFromFile(TextureFixed * texture, const std::string & filePath);
	void referenceCounterUpdate();
	///Note: don't use it to delete textures that will be used \
		used unly in ReloadTextures()
	void deleteUnusedTextures();

public:
	TextureManager();
	~TextureManager();

	void SetTexturesPaths(const std::vector<std::string> & paths);
	bool AddPath(const std::string & path);
	bool DelPath(const std::string & path);

	///Reloads textures, use when scene / level is loading
	void ReloadTextures();

	const TextureFixed * GetTexture(const std::string & tag);
	const TextureFixed * GetTexture(const size_t & id);
	///	Call it in destructor of class that use reference of texture \
		(I think that only Sprite specialized class should use it)
	void GiveBackTexture(const TextureFixed * texture);

	void Update();

private:
	std::vector<TextureFixed*> m_textures;
	std::vector<std::string> m_pathsToFiles;
	size_t m_currentIDcounter;
};

