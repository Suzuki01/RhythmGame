#include <list>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "game_object.h"
#include "input.h"
#include "imgui_setup.h"
#include "sound.h"
#include "audio_clip.h"
#include "scene.h"
#include "title_scene.h"
#include "result_scene.h"
#include "game_scene.h"
#include "notes.h"
#include "texture_manager.h"


Scene* CManager::m_pScene = nullptr;
Notes* g_Notes;

void CManager::Init()
{
	CRenderer::Init();
	Input::Init();
	CAudioClip::Init();
	//CTexture::TextureLoad();
	SetScene<TitleScene>();
	//g_Sound = new Sound;
	Sound::Init("asset/sound/FIRE-GROUND.wav", 114);
	Notes::Load("asset/music_score/fireground.csv");

	ImguiSetup::Init();
}

void CManager::Uninit()
{
	m_pScene->UnInit();
	delete m_pScene;

	delete g_Notes;
	//Input::UnInit(); ‚Ü‚¾ì‚Á‚Ä‚¢‚È‚¢
	CRenderer::Uninit();
	Sound::UnInit();
	TextureManager::Release();
	ImguiSetup::UnInit();
	CAudioClip::Uninit();
}

void CManager::Update()
{
	Input::Update();
	Sound::Update();
	ImguiSetup::Update();
	m_pScene->Update();
	if (Input::Keyboard_IsTrigger(VK_RETURN)) {
//		Sound::Start();
	}
	if (Input::Keyboard_IsTrigger(VK_SPACE)) {
		Sound::Reset();
	}
}

void CManager::Draw()
{
	CRenderer::Begin();
	m_pScene->Draw();
	ImguiSetup::Draw();
	CRenderer::End();

}

Scene* CManager::GetScene() {
	return m_pScene;
}
