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
	static int m_playLength;

	static BOOL Init(int id);
	static void Update();
	static void UnInit();
	static void Start();
	static void Draw();
	static void Stop();
	static void Restart();
	static BOOL ReadWaveFile(LPTSTR lpszFileName, LPWAVEFORMATEX lpwf, LPBYTE* lplpData, LPDWORD lpdwDataSize);
	static float GetTime();
	static int GetSamplingNumber();
	static DWORD GetCurrentSamplingPerSec();
	static float GetCurrentBeats();
	static void Reset();
	static int GetSongSize();
	static void SetTime();
	static void SetPosition();
	static int GetBpm();
};

#endif //!SOUND_H_