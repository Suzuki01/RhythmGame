
#include "main.h"
#include "imgui_setup.h"
#include "audio_clip.h"

IXAudio2*				CAudioClip::m_Xaudio;
IXAudio2MasteringVoice*	CAudioClip::m_MasteringVoice;
XAUDIO2_VOICE_STATE		CAudioClip::m_State;

void CAudioClip::Init(void)
{
	
	// COM初期化
	CoInitializeEx( NULL, COINIT_MULTITHREADED );

	// XAudio生成
	XAudio2Create( &m_Xaudio, 0 );

	// マスタリングボイス生成
	m_Xaudio->CreateMasteringVoice( &m_MasteringVoice );

}


void CAudioClip::Uninit(void)
{

	m_MasteringVoice->DestroyVoice();

	m_Xaudio->Release();

	CoUninitialize();

}








bool CAudioClip::Load(const char *FileName)
{

	// サウンドデータ読込
	WAVEFORMATEX wfx = { 0 };

	{
		HMMIO hmmio = NULL;
		MMIOINFO mmioinfo = { 0 };
		MMCKINFO riffchunkinfo = { 0 };
		MMCKINFO datachunkinfo = { 0 };
		MMCKINFO mmckinfo = { 0 };
		UINT32 buflen;
		LONG readlen;


		hmmio = mmioOpen((LPSTR)FileName, &mmioinfo, MMIO_READ);

		if (hmmio == nullptr) {
			return false;
		}
		riffchunkinfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmioDescend(hmmio, &riffchunkinfo, NULL, MMIO_FINDRIFF);

		mmckinfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend(hmmio, &mmckinfo, &riffchunkinfo, MMIO_FINDCHUNK);

		if (mmckinfo.cksize >= sizeof(WAVEFORMATEX))
		{
			mmioRead(hmmio, (HPSTR)&wfx, sizeof(wfx));
		}
		else
		{
			PCMWAVEFORMAT pcmwf = { 0 };
			mmioRead(hmmio, (HPSTR)&pcmwf, sizeof(pcmwf));
			memset(&wfx, 0x00, sizeof(wfx));
			memcpy(&wfx, &pcmwf, sizeof(pcmwf));
			wfx.cbSize = 0;
		}
		mmioAscend(hmmio, &mmckinfo, 0);

		datachunkinfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(hmmio, &datachunkinfo, &riffchunkinfo, MMIO_FINDCHUNK);



		buflen = datachunkinfo.cksize;
		m_SoundData = new unsigned char[buflen];
		readlen = mmioRead(hmmio, (HPSTR)m_SoundData, buflen);


		m_Length = readlen;
		m_PlayLength = readlen / wfx.nBlockAlign;


		mmioClose(hmmio, 0);
	}


	// サウンドソース生成
	for (int j = 0; j < SOUND_SOURCE_MAX; j++)
	{
		m_Xaudio->CreateSourceVoice(&m_SourceVoice[j], &wfx);
	}
	return true;
}

void CAudioClip::Update() {
	for (int j = 0; j < SOUND_SOURCE_MAX; j++) {
		m_SourceVoice[0]->GetState(&m_State);
	}

}
 
void CAudioClip::Unload()
{

	for (int j = 0; j < SOUND_SOURCE_MAX; j++)
	{
		if (m_SourceVoice[j])
		{
			m_SourceVoice[j]->Stop();
			m_SourceVoice[j]->DestroyVoice();
			m_SourceVoice[j] = NULL;
		}
	}

	if (m_SoundData)
	{
		delete[] m_SoundData;
		m_SoundData = nullptr;
	}



}





void CAudioClip::Play( bool Loop )
{

	for( int j = 0; j < SOUND_SOURCE_MAX; j++ )
	{
		XAUDIO2_VOICE_STATE state;

		m_SourceVoice[j]->GetState( &state );

		if( state.BuffersQueued == 0 )
		{
			//Sound->SourceVoice->Stop();
			//Sound->SourceVoice->FlushSourceBuffers();


			// バッファ設定
			XAUDIO2_BUFFER bufinfo;

			memset(&bufinfo,0x00,sizeof(bufinfo));
			bufinfo.AudioBytes = m_Length;
			bufinfo.pAudioData = m_SoundData;
			bufinfo.PlayBegin = (UINT32)ImguiSetup::GetStartBeats();
			bufinfo.PlayLength = m_PlayLength;
			
			// ループ設定
			if( Loop )
			{
				bufinfo.LoopBegin = 0;
				bufinfo.LoopLength = m_PlayLength;
				bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
			}

			m_SourceVoice[j]->SubmitSourceBuffer( &bufinfo, NULL );
			
			// 再生
			m_SourceVoice[j]->Start();
			m_SourceVoice[j]->GetState(&state);
			break;
		}
	}

}


void CAudioClip::Stop()
{
	for (int j = 0; j < SOUND_SOURCE_MAX; j++)
	{
		m_SourceVoice[j]->Stop();
	}
}


UINT64 CAudioClip::GetSamplingNumber() {
	return m_State.SamplesPlayed;
}