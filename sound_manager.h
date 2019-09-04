#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_

#include <unordered_map>

class SoundManager {
public:
	static CAudioClip* Load(std::string FileName);
	static void Release();
private:
	static std::unordered_map<std::string, CAudioClip*>m_SoundEffectIdMap;
};

#endif // !SOUND_MANAGER_H_
