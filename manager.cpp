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
#include "song_selection_scene.h"
#include "notes.h"
#include "texture_manager.h"
#include "mesh_sky.h"


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
#if defined(_DEBUG) || defined(DEBUG)
	ImguiSetup::Init();
#endif
}

void CManager::Uninit()
{
	m_pScene->UnInit();
	delete m_pScene;

	//Input::UnInit(); ‚Ü‚¾ì‚Á‚Ä‚¢‚È‚¢
	CRenderer::Uninit();
	TextureManager::Release();

#if defined(_DEBUG) || defined(DEBUG)
	ImguiSetup::UnInit();
#endif

	CAudioClip::Uninit();

}

void CManager::Update()
{
	Sound::Update();

	Input::Update();
#if defined(_DEBUG) || defined(DEBUG)
	ImguiSetup::Update();
#endif
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
#if defined(_DEBUG) || defined(DEBUG)
	ImguiSetup::Draw();
#endif
	CRenderer::End();
}

Scene* CManager::GetScene() {
	return m_pScene;
}
