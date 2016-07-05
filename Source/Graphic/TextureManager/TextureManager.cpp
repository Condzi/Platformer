#include "TextureManager.hpp"


bool TextureManager::loadFromFile(TextureFixed & texture, const std::string & filePath)
{
	return texture.loadFromFile(filePath);
}

void TextureManager::referenceCounterUpdate()
{
	for (size_t i = 0; i< m_textures.size(); ++i)
	{
		m_textures[i]->updateReference();
		if (m_textures[i]->m_wishDelete)
		{
			delete m_textures[i];
			m_textures[i] = nullptr;
		}
	}
}

void TextureManager::deleteUnusedTextures()
{
	for (size_t i = 0; i < m_textures.size(); ++i)
	{
		if (m_textures[i] == nullptr)
			m_textures.erase(m_textures.begin(), m_textures.begin() + i);
	}
}

TextureManager::TextureManager()
{
	m_currentIDcounter = 0;
}


TextureManager::~TextureManager()
{
}

void TextureManager::SetTexturesPaths(const std::vector<std::string>& paths)
{
	m_pathsToFiles = paths;
}

bool TextureManager::AddPath(const std::string & path)
{
	if (m_pathsToFiles.size() + 1 > m_pathsToFiles.max_size())
		return false;

	for (std::string var : m_pathsToFiles)
		if (path == var)
			return false;

	m_pathsToFiles.push_back(path);

	return true;
}

bool TextureManager::DelPath(const std::string & path)
{
	for (std::string var : m_pathsToFiles)
		if (path == var)
		{
			var = "";
			return true;
		}

	return false;
}

void TextureManager::ReloadTextures()
{
	// Checking if there is no empty path ("" or " ")
	for (size_t i = 0; i < m_pathsToFiles.size(); ++i)
	{
		if (m_pathsToFiles[i] == "" || m_pathsToFiles[i] == " ")
			m_pathsToFiles.erase(m_pathsToFiles.begin(), m_pathsToFiles.begin() + i);
	}
	
	deleteUnusedTextures();
	m_textures.resize(m_pathsToFiles.size());

	for (size_t i = 0; i < m_pathsToFiles.size(); ++i)
	{
		if (loadFromFile(*m_textures[i], m_pathsToFiles[i]))
		{
			m_textures[i]->tag = m_pathsToFiles[i];
			m_textures[i]->m_textureManagerID = ++m_currentIDcounter;
		}
	}
}

const TextureFixed * TextureManager::GetTexture(const std::string & tag)
{
	for (size_t i = 0; i < m_pathsToFiles.size(); ++i)
	{
		if (m_pathsToFiles[i] == tag && m_textures[i] == nullptr)
		{
			if (loadFromFile(*m_textures[i], m_pathsToFiles[i]))
			{
				m_textures[i]->tag = m_pathsToFiles[i];
				m_textures[i]->m_referenceCounter++;
				return m_textures[i];
			}
			else
				return nullptr;
		}
		else if (m_pathsToFiles[i] == tag)
		{
			m_textures[i]->m_referenceCounter++;
			return m_textures[i];
		}
	}

	return nullptr;
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

void TextureManager::Update()
{
	referenceCounterUpdate();
}
