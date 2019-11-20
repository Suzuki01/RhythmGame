#pragma once

#include <xaudio2.h>



const int SOUND_SOURCE_MAX = 10;


class CAudioClip
{

public:

	static void Init();
	static void Uninit();
	void Update();

	bool Load(const char *FileName);
	void Unload();
	void Play(bool Loop=false);
	void Stop();
	static UINT64 GetSamplingNumber();

private:
	static IXAudio2*				m_Xaudio;
	static IXAudio2MasteringVoice*	m_MasteringVoice;

	IXAudio2SourceVoice*	m_SourceVoice[SOUND_SOURCE_MAX];
	BYTE*					m_SoundData;
	static XAUDIO2_VOICE_STATE		m_State;
	int						m_Length;
	int						m_PlayLength;

};

