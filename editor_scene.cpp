#include "scene.h"
#include "notes.h"
#include "sound.h"
#include "input.h"
#include "editor_scene.h"

void EditorScene::Init()
{
	AddGameObject<CCamera>(CameraLayer)->Init();
	Notes::Load(0);
	Notes::Init();
	Sound::Init(0);
	m_CurrentPosition = 0;
}

void EditorScene::UnInit()
{

}

void EditorScene::Update()
{
	Scene::Update();
	

	if (Input::Keyboard_IsTrigger('R')) {
		Sound::Start();
	}
	if (Input::Keyboard_IsTrigger('F')) {
		Sound::SetPosition();
	}

	if (Input::Keyboard_IsPress(VK_UP)) {
		m_CurrentTime -= 0.25;
	}
	if (Input::Keyboard_IsPress(VK_DOWN)) {
		m_CurrentTime += 0.25;
	}
	if (Sound::GetTime() >= 1.0) {
		m_CurrentBeats++;
	}
	m_CurrentTime = (float)Sound::GetSamplingNumber() * (float)Sound::GetCurrentSamplingPerSec();
	m_CurrentPosition = (float)Sound::GetSamplingNumber() / (Sound::GetCurrentSamplingPerSec() * 60.0f / (float)Sound::GetBpm());
	Notes::Update(m_CurrentPosition);

}

void EditorScene::Draw()
{
	Scene::Draw();
	Notes::Draw();
}

