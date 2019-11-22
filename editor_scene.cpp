#include "scene.h"
#include "notes.h"
#include "sound.h"
#include "input.h"
#include "sound_manager.h"
#include "camera.h"
#include "mesh_field.h"
#include "select_line.h"
#include "audio_clip.h"
#include "imgui_setup.h"
#include "title_scene.h"
#include "editor_scene.h"

float EditorScene::m_CurrentBeats;
float EditorScene::m_CurrentPosition;
float EditorScene::m_CurrentTime;

void EditorScene::Init()
{
	AddGameObject<MeshField>(FieldLayer)->Init(4,16,100,5,20);
	AddGameObject<CCamera>(CameraLayer)->Init();
	AddGameObject<SelectLine>(CursorLayer)->Init("asset/white.jpg",XMFLOAT3(-7.0f,0.0f,1.0f),2.0f,1.0f,4,3.7f);
	AddGameObject<Field>(FieldLayer)->Init();
	Notes::Init();
	Score::Init(5);
	m_CurrentPosition = 0;
	m_CurrentBeats = 1.0f;
	Sound::Start();
	Sound::Stop();
}

void EditorScene::UnInit()
{

}

void EditorScene::Update()
{
	Scene::Update();
	if (Input::Keyboard_IsTrigger('A')) {
		if(ImguiSetup::m_isNoteCreate)
			Notes::Create(1,0);
	}
	if (Input::Keyboard_IsTrigger('D')) {
		if (ImguiSetup::m_isNoteCreate)
			Notes::Create(2, 0);
	}
	if (Input::Keyboard_IsTrigger('J')) {
		if (ImguiSetup::m_isNoteCreate)
			Notes::Create(3, 0);
	}
	if (Input::Keyboard_IsTrigger('L')) {
		if (ImguiSetup::m_isNoteCreate)
			Notes::Create(4, 0);
	}
	if (Input::Keyboard_IsTrigger('R')) {
		m_CurrentBeats = Sound::GetEditorCurrenntBeats();
		Sound::Restart();
	}
	if (Input::Keyboard_IsTrigger(VK_SPACE)) {
		Notes::Save();
		Sound::m_Samples = 0;
		CManager::SetScene<TitleScene>();
	}
	if (Input::Keyboard_IsPress('S')) {
		m_CurrentBeats = Sound::GetSamplingNumber();
		Sound::Stop();
	}
	//曲の再生位置移動
	if (Input::Keyboard_IsPress(VK_DOWN)) {
		if (!Sound::isPlay) {
			m_CurrentBeats -= Sound::GetCurrentSamplingPerSec() / 60.0f;
			if (m_CurrentBeats < 0.0f) {
				m_CurrentBeats = 0.0f;
			}
		}
	}
	if (Input::Keyboard_IsPress(VK_UP)) {
		if (!Sound::isPlay) {
			m_CurrentBeats += Sound::GetCurrentSamplingPerSec() / 60.0f;
			if (m_CurrentBeats > Sound::m_playLength) {
				m_CurrentBeats = Sound::m_playLength;
			}
		}
	}
		Sound::SetPosition(m_CurrentBeats);

	// TODO　マウスのクリックで画面内のノーツを選択しているか判定する処理の作成
	if (Input::Keyboard_IsTrigger(VK_LBUTTON)) {
		POINT mousePos;
		bool cursor = GetCursorPos(&mousePos);
		XMFLOAT2 cursorPos;
		cursor = ScreenToClient(GetWindow(),&mousePos);
		//ここにマウス座標にノーツを配置する関数を追加
	}

	if (Input::Keyboard_IsTrigger(VK_RETURN)) {
		if(!Notes::CheckNotes(CManager::GetScene()->GetComponent<SelectLine>(CursorLayer)->m_Billboard->m_Transform.Position,0.3f, CManager::GetScene()->GetComponent<SelectLine>(CursorLayer)->m_RaneNumber))
			Notes::Create(CManager::GetScene()->GetComponent<SelectLine>(CursorLayer)->m_RaneNumber, CManager::GetScene()->GetComponent<SelectLine>(CursorLayer)->m_Billboard->m_Transform.Position.z);
	}
	Notes::Update();
}

void EditorScene::Draw()
{
	Scene::Draw();
	Notes::Draw();
	Score::SongPositionDraw();
}

float EditorScene::GetCurrentBeats() {
	return m_CurrentPosition;
}

