#ifndef SOUND_H_
#define SOUND_H_

class Sound {
public:
	static LPBYTE       m_lpWaveData;
	static HWAVEOUT     m_hwo;
	static WAVEHDR      m_wh;
	static WAVEFORMATEX m_wf;
	static float m_dwSecond;
	static MMTIME m_mmt;
	static int m_bpm;

	static BOOL Init(char* name, int bpm);
	static void Update();
	static void UnInit();
	static void Start();
	static void Draw();
	static BOOL ReadWaveFile(LPTSTR lpszFileName, LPWAVEFORMATEX lpwf, LPBYTE* lplpData, LPDWORD lpdwDataSize);
	static float GetTime();
	static DWORD GetSamplingNumber();
	static DWORD GetCurrentSamplingPerSec();
	static float GetCurrentBeats();
	static void Reset();
};

#endif //!SOUND_H_