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
		XMFLOAT3 worldMousePos = CalcScreenToXZ(mousePos.x,mousePos.y,SCREEN_WIDTH,SCREEN_HEIGHT,&CManager::GetScene()->GetComponent<CCamera>(CameraLayer)->GetViewMatrix(), &CManager::GetScene()->GetComponent<CCamera>(CameraLayer)->GetProjectMatrix());
		//ここにマウス座標にノーツを配置する関数を追加
		if(!Notes::CheckNotes(worldMousePos, 0.5f,JudgeRane(-8.0f,worldMousePos.x)))
			Notes::Create(JudgeRane(-8.0f,worldMousePos.x),worldMousePos.z);
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

int EditorScene::JudgeRane(float startPosX,float x)
{
	for (int i = 0; i < RANE_MAX; i++) {
		if (startPosX + (i * 4.0f) < x && x < startPosX + ((i + 1) * 4.0f)) {
			return i + 1;
		}
	}
	return 0;
	//    Sx = (FLOAT)Sx* ((FLOAT)SCREEN_WIDTH/(FLOAT))

/*	XMFLOAT3 v;
	//
	v.x = (((2.0 * Sx) / (float)SCREEN_WIDTH) - 1) / Prj[0].r->m128_f32[0];
	v.y = -(((2.0 * Sy) / (float)SCREEN_HEIGHT) - 1) / Prj[1].r->m128_f32[1];
	v.z = 1.0;
	XMFLOAT3 pos = GetComponent<MeshField>(FieldLayer)->m_Transform.Position;
	XMMATRIX worldView = *world * *View;
	XMMATRIX m = XMMatrixInverse(nullptr, worldView);
	XMFLOAT3 vRayDir;
	XMFLOAT3 vStartPoint;
	vRayDir.x = v.x * m.r[0].m128_f32[0] + v.y * m.r[1].m128_f32[0] + v.z * m.r[2].m128_f32[0];
	vRayDir.y = v.x * m.r[0].m128_f32[1] + v.y * m.r[1].m128_f32[1] + v.z * m.r[2].m128_f32[1];
	vRayDir.z = v.x * m.r[0].m128_f32[2] + v.y * m.r[1].m128_f32[2] + v.z * m.r[2].m128_f32[2];
	XMVECTOR vec = XMVector3Normalize(XMLoadFloat3(&vRayDir));
	XMStoreFloat3(&vStartPoint, vec);
    vStartPoint.x = m.r[3].m128_f32[0];
    vStartPoint.y = m.r[3].m128_f32[1];
    vStartPoint.z = m.r[3].m128_f32[2];
	*/
}

XMFLOAT3 EditorScene::CalcScreenToWorld(
	int Sx,  // 
	int Sy,  // 
	float fZ,  //
	int Screen_w,
	int Screen_h,
	XMMATRIX* View,
	XMMATRIX* Prj)
{
	// 各行列の逆行列を算出
	XMMATRIX InvView, InvPrj, VP, InvViewport;
	InvView = XMMatrixInverse(nullptr, *View);
	InvPrj = XMMatrixInverse(nullptr, *Prj);
	VP = XMMatrixIdentity();
	VP.r[0].m128_f32[0] = Screen_w / 2.0f;
	VP.r[1].m128_f32[1] = -Screen_h / 2.0f;
	VP.r[3].m128_f32[0] = Screen_w / 2.0f;
	VP.r[3].m128_f32[1] = Screen_h / 2.0f;
	InvViewport = XMMatrixInverse(nullptr, VP);

	// 逆変換
	XMMATRIX tmp = InvViewport * InvPrj * InvView;
	XMVECTOR vec = XMVector3TransformCoord(XMLoadFloat3(&XMFLOAT3(Sx, Sy, fZ)), tmp);
	XMFLOAT3 pos;
	XMStoreFloat3(&pos, vec);
	return pos;
}

XMFLOAT3 EditorScene::CalcScreenToXZ(int Sx, int Sy, int Screen_w, int Screen_h, XMMATRIX* View, XMMATRIX* Prj)
{
	XMFLOAT3 nearpos;
	XMFLOAT3 farpos;
	XMFLOAT3 rayPos;
	XMFLOAT3 intersection;
	nearpos = CalcScreenToWorld(Sx, Sy, 0.0f, Screen_w, Screen_h, View, Prj);
	farpos = CalcScreenToWorld(Sx, Sy, 1.0f, Screen_w, Screen_h, View, Prj);
	rayPos.x = farpos.x - nearpos.x;
	rayPos.y = farpos.y - nearpos.y;
	rayPos.z = farpos.z - nearpos.z;

	XMVECTOR ray = XMVector3Normalize(XMLoadFloat3(&rayPos));
	XMStoreFloat3(&rayPos,ray);
	// 床との交差が起きている場合は交点を
	// 起きていない場合は遠くの壁との交点を出力
	if (rayPos.y <= 0) {
		XMFLOAT3 up = { 0.0f,1.0f,0.0f };
		// 床交点
		XMVECTOR Lray = XMVector3Dot(ray,XMVECTOR(XMLoadFloat3(&up)));
		XMVECTOR LP0 = XMVector3Dot(-XMLoadFloat3(&nearpos),XMVECTOR(XMLoadFloat3(&up)));
		
//		float Lray = D3DXVec3Dot(&ray, &D3DXVECTOR3(0, 1, 0));
//		float LP0 = D3DXVec3Dot(&(-nearpos), &D3DXVECTOR3(0, 1, 0));
		XMFLOAT3 n;
		XMStoreFloat3(&n,LP0/Lray);
		intersection.x = nearpos.x + n.x * rayPos.x;
		intersection.y = nearpos.y + n.y * rayPos.y;
		intersection.z = nearpos.z + n.z * rayPos.z;
	}
	else {
		intersection = farpos;
	}

	return intersection;
}

