#pragma once
#include "..\TextureFixed.hpp"

class TextureManager
{
private:
	bool loadFromFile(const std::string & filePath);

public:
	TextureManager();
	~TextureManager();

	void ReloadTextures();

private:

};

