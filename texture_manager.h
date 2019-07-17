#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include <unordered_map>

class TextureManager {
public:
	static CTexture* Load(std::string FileName);
	static void Release();
private:
	static std::unordered_map<std::string,CTexture*>m_TextureIdMap;
};

#endif // !TEXTURE_MANAGER_H_
