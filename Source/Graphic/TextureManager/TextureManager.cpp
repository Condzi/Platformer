#include "TextureManager.hpp"



TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

void TextureManager::GiveBackTexture(TextureFixed * texture)
{
	for (TextureFixed * var : m_textures)
	{
		//If they're pointing the same texture...
		if (&var == &texture)
		{
			var->m_referenceCounter--;
			var->updateReference();
		}
	}
}
