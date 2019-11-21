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
		Notes::Create(1,0);
	}
	if (Input::Keyboard_IsTrigger('D')) {
		Notes::Create(2, 0);
	}
	if (Input::Keyboard_IsTrigger('J')) {
		Notes::Create(3, 0);
	}
	if (Input::Keyboard_IsTrigger('L')) {
		Notes::Create(4, 0);
	}
	if (Input::Keyboard_IsTrigger('R')) {
		m_CurrentBeats = Sound::GetEditorCurrenntBeats();

		Sound::Restart();
		//audio->Play();
	}
	if (Input::Keyboard_IsTrigger('F')) {
	//	Sound::SetPosition(ImguiSetup::GetStartBeats());
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
		JudgeRane(mousePos.x,mousePos.y,0.01f,SCREEN_WIDTH,SCREEN_HEIGHT,&CManager::GetScene()->GetComponent<CCamera>(CameraLayer)->GetViewMatrix(), &CManager::GetScene()->GetComponent<CCamera>(CameraLayer)->GetProjectMatrix(), &CManager::GetScene()->GetComponent<CCamera>(CameraLayer)->GetWorldMatrix());
		NoteCreate();
	}

	if (Input::Keyboard_IsTrigger(VK_RETURN)) {
		if(!Notes::CheckNotes(CManager::GetScene()->GetComponent<SelectLine>(CursorLayer)->m_Billboard->m_Transform.Position,0.3f, CManager::GetScene()->GetComponent<SelectLine>(CursorLayer)->m_RaneNumber))
			Notes::Create(CManager::GetScene()->GetComponent<SelectLine>(CursorLayer)->m_RaneNumber, CManager::GetScene()->GetComponent<SelectLine>(CursorLayer)->m_Billboard->m_Transform.Position.z);
	}

//	m_CurrentTime = (float)Sound::GetSamplingNumber() * (float)Sound::GetCurrentSamplingPerSec();
//	m_CurrentPosition = (float)Sound::GetEditorCurrenntBeats();

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

int EditorScene::JudgeRane(
	int Sx,  // スクリーンX座標
	int Sy,  // スクリーンY座標
	float fZ,  // 射影空間でのZ値（0～1）
	int Screen_w,
	int Screen_h,
	XMMATRIX* View,
	XMMATRIX* Prj,
	XMMATRIX* world) 
{
//	Sx = (FLOAT)Sx* ((FLOAT)SCREEN_WIDTH/(FLOAT))

	XMFLOAT3 v;
	//マウス座標をスクリーンの中心が原点になるように補正（正規化）
	v.x = (((2.0 * Sx) / (float)SCREEN_WIDTH) - 1) / Prj[0].r->m128_f32[0];
	v.y = -(((2.0 * Sy) / (float)SCREEN_HEIGHT) - 1) / Prj[1].r->m128_f32[1];
	v.z = 1.0;
//	XMFLOAT3 pos = GetComponent<MeshField>(FieldLayer)->m_Transform.Position;
	XMMATRIX worldView = *world * *View;
	XMMATRIX m = XMMatrixInverse(nullptr,worldView);
	XMFLOAT3 vRayDir;
	XMFLOAT3 vStartPoint;
	vRayDir.x = v.x * m.r[0].m128_f32[0] + v.y * m.r[1].m128_f32[0] + v.z * m.r[2].m128_f32[0];
	vRayDir.y = v.x * m.r[0].m128_f32[1] + v.y * m.r[1].m128_f32[1] + v.z * m.r[2].m128_f32[1];
	vRayDir.z = v.x * m.r[0].m128_f32[2] + v.y * m.r[1].m128_f32[2] + v.z * m.r[2].m128_f32[2];
	XMVECTOR vec = XMVector3Normalize(XMLoadFloat3(&vRayDir));
	XMStoreFloat3(&vStartPoint,vec);
//	vStartPoint.x = m.r[3].m128_f32[0];
//	vStartPoint.y = m.r[3].m128_f32[1];
//	vStartPoint.z = m.r[3].m128_f32[2];
/*
	XMMATRIX InvView, InvPrj, VP, InvViewport;

	
	InvView = XMMatrixInverse(nullptr,*View);
	InvPrj = XMMatrixInverse(nullptr,*Prj);
	VP = XMMatrixIdentity();
	VP.r[0].m128_f32[0] = Screen_w / 2.0f;
	VP.r[1].m128_f32[1] = -Screen_h / 2.0f;
	VP.r[3].m128_f32[0] = Screen_w / 2.0f;
	VP.r[3].m128_f32[1] = Screen_h / 2.0f;
	InvViewport = XMMatrixInverse(NULL, VP);
	XMMATRIX tmp = InvViewport * InvPrj * InvView;
	XMVECTOR vec = XMVector3TransformCoord(XMLoadFloat3(&XMFLOAT3(Sx,Sy,fZ)),tmp);
	XMFLOAT3 mouseWorldPos = {0,0,0};
	XMStoreFloat3(&mouseWorldPos,vec);
	CManager::GetScene()->AddGameObject<Player>(PlayerLayer)->Init(mouseWorldPos);
//	CManager::GetScene()->GetComponent<Player>(PlayerLayer)->m_Transform.Position = mouseWorldPos;
	//XMVector4Transform();C
*/
//	CManager::GetScene()->GetComponent<Ball>(PlayerLayer)->m_Transform.Position = vStartPoint;
	return 0;
}

void EditorScene::NoteCreate()
{

}

