#include "main.h"
#include "audio_clip.h"
#include "sound_manager.h"

std::unordered_map<std::string, CAudioClip*>SoundManager::m_SoundEffectIdMap;


CAudioClip* SoundManager::Load(std::string FileName)
{
	if (m_SoundEffectIdMap.count(FileName) != 0) {
		return m_SoundEffectIdMap[FileName];
	}
	else {
		CAudioClip* sound = new CAudioClip;
		if (sound->Load(FileName.c_str())) {
			m_SoundEffectIdMap[FileName] = sound;
			return m_SoundEffectIdMap[FileName];
		}
		else {
			return nullptr;
		}
	}
}

void SoundManager::Release()
{
	for (auto itr = m_SoundEffectIdMap.begin(); itr != m_SoundEffectIdMap.end();) {
		delete itr->second;
		itr = m_SoundEffectIdMap.erase(itr);
	}
}
