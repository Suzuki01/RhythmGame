#ifndef SOUND_H_
#define SOUND_H_

typedef struct _WOSP {
	WORD nBlockAlign;
	DWORD nAvgBytesPerSec;
}WOSP;

class Sound {
public:
	static WAVEHDR      m_whdr;
	static LPBYTE       m_lpWaveData;
	static HWAVEOUT     m_hwo;
	static WAVEHDR      m_wh;
	static WAVEFORMATEX m_wf;
	static float        m_dwSecond;
	static MMTIME       m_mmt;
	static int          m_bpm;
	static int          m_playLength;

	static BOOL  Init(int id);
	static void  Update();
	static void  UnInit();
	static void  Start();
	static void  Stop();
	static void  Reset();
	static void  Restart();
	static BOOL  ReadWaveFile(LPTSTR lpszFileName, LPWAVEFORMATEX lpwf, LPBYTE* lplpData, LPDWORD lpdwDataSize);
	static float GetTime();
	static int   GetSamplingNumber();
	static int   GetEditorSamplingNumber();
	static DWORD GetCurrentSamplingPerSec();
	static float GetCurrentBeats();
	static float GetEditorCurrenntBeats();
	static int   GetSongSize();
	static int   GetBpm();
	static void  SetTime();
	static void  SetPosition(DWORD samples);
	static void  SetPositionUnprepareHeader(HWAVEOUT hwo);
	static int   WaveOutSetPosition(HWAVEOUT hwo, LPWAVEHDR pwh, LPMMTIME pmmt, WOSP* wosp);
	static void  ImguiSoudData();

	static WOSP  m_Wosp;
	static DWORD m_LastSamples;  
	static DWORD m_Samples;
	static bool  isPlay;
private:
};

#endif //!SOUND_H_