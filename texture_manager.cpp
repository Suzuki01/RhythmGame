#include "main.h"
#include "texture.h"
#include "texture_manager.h"

std::unordered_map<std::string, CTexture*>TextureManager::m_TextureIdMap;


CTexture* TextureManager::Load(std::string FileName)
{
	if (m_TextureIdMap.count(FileName) != 0) {
		return m_TextureIdMap[FileName];
	}
	else {
		CTexture* tex = new CTexture;
		if (tex->LoadTexture(FileName.c_str())) {
			m_TextureIdMap[FileName] = tex;
			return m_TextureIdMap[FileName];
		}
		else {
			return nullptr;
		}
	}
}

void TextureManager::Release()
{
	for (auto itr = m_TextureIdMap.begin(); itr != m_TextureIdMap.end();) {
		delete itr->second;
		itr = m_TextureIdMap.erase(itr);		
	}
}

