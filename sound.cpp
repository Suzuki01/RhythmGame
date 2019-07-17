#include "main.h"
#include "sound.h"

LPBYTE       Sound::m_lpWaveData = NULL;
HWAVEOUT     Sound::m_hwo = NULL;
WAVEHDR      Sound::m_wh = { 0 };
WAVEFORMATEX Sound::m_wf = { 0 };
float  Sound::m_dwSecond = 0;
float time = 0;
MMTIME Sound::m_mmt = { 0 };
int Sound::m_bpm = 0;


BOOL Sound::Init(char* name, int bpm) {
	DWORD dwDataSize;
	m_bpm = bpm;
	if (!ReadWaveFile((LPTSTR)TEXT(name), &m_wf, &m_lpWaveData, &dwDataSize))
		return -1;

	if (waveOutOpen(&m_hwo, WAVE_MAPPER, &m_wf, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
		MessageBox(NULL, TEXT("WAVEデバイスのオープンに失敗しました。"), NULL, MB_ICONWARNING);
		return -1;
	}

	m_wh.lpData = (LPSTR)m_lpWaveData;
	m_wh.dwBufferLength = dwDataSize;
	m_wh.dwFlags = 0;
	waveOutPrepareHeader(m_hwo, &m_wh, sizeof(WAVEHDR));
}

void Sound::UnInit() {
	if (m_hwo != NULL) {
		waveOutReset(m_hwo);
		waveOutUnprepareHeader(m_hwo, &m_wh, sizeof(WAVEHDR));
		waveOutClose(m_hwo);
	}

	if (m_lpWaveData != NULL)
		HeapFree(GetProcessHeap(), 0, m_lpWaveData);
}

void Sound::Update() {

	m_mmt.wType = TIME_SAMPLES;
	waveOutGetPosition(m_hwo, &m_mmt, sizeof(MMTIME)); //

	m_dwSecond = (float)m_mmt.u.cb / (float)m_wf.nSamplesPerSec; //cb今流してるサンプリングデータの番号　wf.nSam 一秒間に何サンプリング
}


BOOL Sound::ReadWaveFile(LPTSTR lpszFileName, LPWAVEFORMATEX lpwf, LPBYTE* lplpData, LPDWORD lpdwDataSize)
{
	HMMIO    hmmio;
	MMCKINFO mmckRiff;
	MMCKINFO mmckFmt;
	MMCKINFO mmckData;
	LPBYTE   lpData;

	hmmio = mmioOpen(lpszFileName, NULL, MMIO_READ);
	if (hmmio == NULL) {
		MessageBox(NULL, TEXT("ファイルのオープンに失敗しました。"), NULL, MB_ICONWARNING);
		return FALSE;
	}

	mmckRiff.fccType = mmioStringToFOURCC(TEXT("WAVE"), 0);
	if (mmioDescend(hmmio, &mmckRiff, NULL, MMIO_FINDRIFF) != MMSYSERR_NOERROR) {
		MessageBox(NULL, TEXT("WAVEファイルではありません。"), NULL, MB_ICONWARNING);
		mmioClose(hmmio, 0);
		return FALSE;
	}

	mmckFmt.ckid = mmioStringToFOURCC(TEXT("fmt "), 0);
	if (mmioDescend(hmmio, &mmckFmt, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
		mmioClose(hmmio, 0);
		return FALSE;
	}
	mmioRead(hmmio, (HPSTR)lpwf, mmckFmt.cksize);
	mmioAscend(hmmio, &mmckFmt, 0);
	if (lpwf->wFormatTag != WAVE_FORMAT_PCM) {
		MessageBox(NULL, TEXT("PCMデータではありません。"), NULL, MB_ICONWARNING);
		mmioClose(hmmio, 0);
		return FALSE;
	}

	mmckData.ckid = mmioStringToFOURCC(TEXT("data"), 0);
	if (mmioDescend(hmmio, &mmckData, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
		mmioClose(hmmio, 0);
		return FALSE;
	}
	lpData = (LPBYTE)HeapAlloc(GetProcessHeap(), 0, mmckData.cksize);
	mmioRead(hmmio, (HPSTR)lpData, mmckData.cksize);
	mmioAscend(hmmio, &mmckData, 0);

	mmioAscend(hmmio, &mmckRiff, 0);
	mmioClose(hmmio, 0);

	*lplpData = lpData;
	*lpdwDataSize = mmckData.cksize;

	return TRUE;
}

void Sound::Start() {
	waveOutWrite(m_hwo, &m_wh, sizeof(WAVEHDR));
}

float Sound::GetTime() {
	return m_dwSecond;
}

DWORD Sound::GetSamplingNumber() {
	return m_mmt.u.cb;
}

DWORD Sound::GetCurrentSamplingPerSec() {
	return m_wf.nSamplesPerSec;
}

float Sound::GetCurrentBeats() {
	return (float)m_mmt.u.cb / ((float)m_wf.nSamplesPerSec * 60.0f / (float)m_bpm);
}

void Sound::Reset() {
	waveOutRestart(m_hwo);
	waveOutReset(m_hwo);
}

