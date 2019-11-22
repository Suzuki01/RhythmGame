#include "main.h"
#include "sound.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"


LPBYTE       Sound::m_lpWaveData = NULL;
HWAVEOUT     Sound::m_hwo = NULL;
WAVEHDR      Sound::m_wh = { 0 };
WAVEHDR		 Sound::m_whdr = { 0 };
WAVEFORMATEX Sound::m_wf = { 0 };
float  Sound::m_dwSecond = 0;
float time = 0;
MMTIME Sound::m_mmt = { 0 };
int Sound::m_bpm = 0;
int Sound::m_playLength = 0;
WOSP Sound::m_Wosp;
DWORD Sound::m_LastSamples = 0;
DWORD Sound::m_Samples = 0;
bool Sound::isPlay = false;

typedef struct {
	const char* song;
	int bpm;
}SongData;

SongData data[] = {
		{{"asset/sound/kurumiwari_ningyou.wav"},144 },
		{{"asset/sound/tengokuto_jigoku.wav"},83},
		{{"asset/sound/aisi.wav"},100 },
};


BOOL Sound::Init(int id) {
	DWORD dwDataSize;
	m_bpm = data[id].bpm;
	if (!ReadWaveFile((LPTSTR)TEXT(data[id].song), &m_wf, &m_lpWaveData, &dwDataSize))
		return -1;

	if (waveOutOpen(&m_hwo, WAVE_MAPPER, &m_wf, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
		MessageBox(NULL, TEXT("WAVEデバイスのオープンに失敗しました。"), NULL, MB_ICONWARNING);
		return -1;
	}
	waveOutSetVolume(m_hwo,25000);
	m_wh.lpData = (LPSTR)m_lpWaveData;
	m_wh.dwBufferLength = dwDataSize;
	m_wh.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
	m_wh.dwLoops = 1;
	waveOutPrepareHeader(m_hwo, &m_wh, sizeof(WAVEHDR));

	m_playLength = m_wh.dwBufferLength / m_wf.nBlockAlign;
	m_Wosp.nBlockAlign = Sound::m_wf.nBlockAlign;
	m_Wosp.nAvgBytesPerSec = Sound::m_wf.nAvgBytesPerSec;
	m_LastSamples = 0;
//	Start();
}

void Sound::UnInit() {
	if (m_hwo != NULL) {
		waveOutReset(m_hwo);
		Sound::SetPositionUnprepareHeader(m_hwo);
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
	isPlay = true;
}

void Sound::Stop()
{
	waveOutPause(m_hwo);
	isPlay = false;
}

void Sound::Restart()
{
	waveOutRestart(m_hwo);
	isPlay = true; 
}

//現在の演奏時間取得
float Sound::GetTime() {
	return m_dwSecond;
}

//現在のサンプリング数取得
int Sound::GetSamplingNumber() {
	return (int)m_mmt.u.cb + m_Samples;
}

int Sound::GetEditorSamplingNumber() {
	return (int)m_mmt.u.cb;
}

//1秒間のサンプリング数取得
DWORD Sound::GetCurrentSamplingPerSec() {
	return m_wf.nSamplesPerSec;
}

//現在の拍数取得
float Sound::GetCurrentBeats() {
	return ((float)m_mmt.u.cb + (float)m_Samples) / ((float)m_wf.nSamplesPerSec * 60.0f / (float)m_bpm);
}

float Sound::GetEditorCurrenntBeats() {
	return (float)m_mmt.u.cb / ((float)m_wf.nSamplesPerSec * 60.0f / (float)m_bpm);
}

void Sound::Reset() {
	waveOutRestart(m_hwo);
	waveOutReset(m_hwo);
}

//曲の長さの取得（サンプリング数）
int Sound::GetSongSize() {
	return m_playLength;
}

void Sound::SetPosition(DWORD samples) {
	if (isPlay)
		return;
    m_Samples += samples - m_LastSamples;
	Sound::m_mmt.u.cb = m_Samples;
	Sound::WaveOutSetPosition(Sound::m_hwo, &Sound::m_wh, &Sound::m_mmt, &m_Wosp);
	m_LastSamples = m_Samples;
}

int Sound::GetBpm() {
	return m_bpm;
}

int Sound::WaveOutSetPosition(HWAVEOUT hwo, LPWAVEHDR pwh, LPMMTIME pmmt, WOSP* wosp)
{
	DWORD cb;
	switch (pmmt->wType) {
	case TIME_BYTES:
		cb = pmmt->u.cb;
		break;
	case TIME_SAMPLES:
		cb = pmmt->u.sample * wosp->nBlockAlign;
		break;
	case TIME_MS:
		cb = pmmt->u.ms * wosp->nAvgBytesPerSec / 1000;
		break;
	default:
		return -1;
	}
	if (cb % wosp->nBlockAlign) {
		if ((cb % wosp->nBlockAlign) <= (wosp->nBlockAlign / 2)) {
			cb -= (cb % wosp->nBlockAlign);
		}
		else {
			cb += (wosp->nBlockAlign - (cb % wosp->nBlockAlign));
		}
	}
	if (cb < 0 || cb >= pwh->dwBufferLength) return -2;

	waveOutReset(hwo);
	SetPositionUnprepareHeader(hwo);

	ZeroMemory(&m_whdr, sizeof(WAVEHDR));
	m_whdr.lpData = pwh->lpData + cb;
	m_whdr.dwBufferLength = pwh->dwBufferLength - cb;
	m_whdr.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
	m_whdr.dwLoops = 1;

	waveOutPrepareHeader(hwo, &m_whdr, sizeof(WAVEHDR));
	waveOutWrite(hwo, &m_whdr, sizeof(WAVEHDR));
	Stop();
	
	return 0;
}

void Sound::SetPositionUnprepareHeader(HWAVEOUT hwo)
{
	if (m_whdr.dwFlags & WHDR_PREPARED) {
		waveOutUnprepareHeader(hwo, &m_whdr, sizeof(WAVEHDR));
	}
}
void Sound::ImguiSoudData() {
	ImGui::Text("Current Time  = %f", Sound::GetTime());
	if(isPlay)
		ImGui::Text("Current Beats = %f", Sound::GetCurrentBeats());
	else {
		ImGui::Text("Current Beats = %f", Sound::GetEditorCurrenntBeats());
	}

	ImGui::Text("EditorBeats = %f", Sound::GetEditorCurrenntBeats());
	ImGui::Text("Beats = %f", Sound::GetCurrentBeats());

	ImGui::Text("Current Sampling Number = %d", Sound::GetSamplingNumber());
	ImGui::Text("Sound Size = %d", Sound::GetSongSize());

}