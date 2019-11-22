#include "main.h"
#include "manager.h"
#include "input.h"
#include "polygon.h"
#include "scene.h"
#include "audio_clip.h"
#include "game_scene.h"
#include "thumbnail.h"
#include "sound.h"
#include "notes.h"
#include "editor_scene.h"
#include "song_selection_scene.h"

char* number[] = {
	{"asset/number/0.png"},
	{"asset/number/1.png"},
	{"asset/number/2.png"},
	{"asset/number/3.png"},
	{"asset/number/4.png"},
	{"asset/number/5.png"},
	{"asset/number/6.png"},
	{"asset/number/7.png"},
	{"asset/number/8.png"},
	{"asset/number/9.png"},
};

char* level[] = {
	{"asset/frame/easy"},
	{"asset/frame/normal"},
	{"asset/frame/expert"},
	{"asset/frame/master"},
};

int on = 0;

CPolygon* g_polygon = new CPolygon;


void SongSelectionScene::Init()
{
	AddGameObject<CPolygon>(0)->Init("asset/press_to_space.png", 345, 500, 397, 84);
	AddGameObject<CPolygon>(0)->Init("asset/select.png", 370, 50, 350, 84);
	on = 0;
	//曲数を取得（現時点では直打ち）
	for (int i = 0; i < 2; i++) {
		CPolygon* polygon = new CPolygon;
		polygon->Init("asset/background.png", 0, 0, 350, 50);
		polygon->m_Transform.Position = { 670.0f,20.0f + 75 * (i+3),0.0f };
		if (i == 0) {
			polygon->m_Transform.Position.x -= 50;
		}
		m_pPolygon.push_back(polygon);
		CPolygon* thumPoly = new CPolygon;
		thumPoly->Init(url[i], 0, 0, 50, 50);
		thumPoly->m_Transform.Position = { 670.0f,20.0f + 75 * (i +3),0.0f };
		if (i == 0) {
			thumPoly->m_Transform.Position.x -= 50;
		}
		m_pThumbnailPolygon.push_back(thumPoly);
	}
	if (Notes::isEditorMode) {
		m_Phase = PHASE_INDEX_SELECT;
	}
	else {
		m_Phase = PHASE_INDEX_START;
	}
	g_polygon = new CPolygon;
	g_polygon->Init("asset/tutorial.png",0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
}


void SongSelectionScene::UnInit()
{
	for (CPolygon* object : m_pPolygon) {
		object->UnInit();
		delete object;
	}

	for (CPolygon* object : m_pThumbnailPolygon) {
		object->UnInit();
		delete object;
	}

	for (CPolygon* object : m_pSelectSongFrame) {
		object->UnInit();
		delete object;
	}

//	Scene::UnInit();
}

void SongSelectionScene::Update()
{

	Scene::Update();
	switch (m_Phase) {
	case PHASE_INDEX_START:
		if (Input::Keyboard_IsTrigger(VK_SPACE))
			m_Phase = PHASE_INDEX_SELECT;
		break;
	case PHASE_INDEX_SELECT:
		//曲画面移動
		if (Input::Keyboard_IsTrigger('W')) {
			if (on == 0)
				break;
			for (CPolygon* object : m_pPolygon) {
				object->m_Transform.Position.y += 75;
				object->m_Transform.Position.x = 670;
				if (object->m_Transform.Position.y == 245.0f) {
					object->m_Transform.Position.x -= 50;
				}
			}
			for (CPolygon* object : m_pThumbnailPolygon) {
				object->m_Transform.Position.y += 75;
				object->m_Transform.Position.x = 670;
				if (object->m_Transform.Position.y == 245.0f) {
					object->m_Transform.Position.x -= 50;
				}
			}
			on = 0;
		}
		if (Input::Keyboard_IsTrigger('S')) {
			if (on == 1)
				break;
			for (CPolygon* object : m_pPolygon) {
				object->m_Transform.Position.y -= 75;
				object->m_Transform.Position.x = 670;
				if (object->m_Transform.Position.y == 245.0f) {
					object->m_Transform.Position.x -= 50;
				}
			}
			for (CPolygon* object : m_pThumbnailPolygon) {
				object->m_Transform.Position.y -= 75;
				object->m_Transform.Position.x = 670;
				if (object->m_Transform.Position.y == 245.0f) {
					object->m_Transform.Position.x -= 50;
				}
			}
			on = 1;
		}

		if (Input::Keyboard_IsTrigger(VK_SPACE)) {
			m_songNumber = DecisionNumber();
			SelectSongFrameCreate(m_songNumber, m_songNumber, m_songNumber);
			Sound::Init(m_songNumber);
			Notes::Load(m_songNumber);
			m_Phase = PHASE_INDEX_DECISION;
		}
		break;
	case PHASE_INDEX_DECISION:
		if (Input::Keyboard_IsTrigger(VK_SPACE)) {
			//UnInit();
			if (Notes::isEditorMode) {
				CManager::SetScene<EditorScene>();
			}
			else {
				CManager::SetScene<GameScene>();
			}
		}
		break;
	}
}

void SongSelectionScene::Draw()
{
	switch (m_Phase) {
	case PHASE_INDEX_START:
		g_polygon->Draw();
		break;
	case PHASE_INDEX_SELECT:
		for (CPolygon* object : m_pPolygon) {
			object->Draw();
		}
		for (CPolygon* object : m_pThumbnailPolygon) {
			object->Draw();
		}
		Scene::Draw();	
		break;
	case PHASE_INDEX_DECISION:
		Scene::Draw();
		for (CPolygon* object : m_pSelectSongFrame) {
			object->Draw();
		}
		break;
	}
}

int SongSelectionScene::DecisionNumber()
{
	int cnt = 0;
	for (CPolygon* object : m_pThumbnailPolygon) {
		if (object->m_Transform.Position.x == 620.0f)
			return cnt;
		cnt++;
	}
}

void SongSelectionScene::SelectSongFrameCreate(int level, int stage, int songNumber)
{
	//レベル表示ポリゴン生成
	CPolygon* polygon = new CPolygon;
	polygon->Init(number[level], 0, 0, 60, 60);
	polygon->m_Transform.Position = { SCREEN_WIDTH * 0.5f - 185.0f,200.0f,0.0f };
	m_pSelectSongFrame.push_back(polygon);

	//サムネイル表示ポリゴン生成
	CPolygon* thumPol = new CPolygon;
	thumPol->Init(url[songNumber], 0, 0, 250, 250);
	thumPol->m_Transform.Position = { SCREEN_WIDTH * 0.5f - 125.0f,200.0f,0.0f };
	m_pSelectSongFrame.push_back(thumPol);

	//レベル別フレームポリゴン生成
	//	polygon = new CPolygon;
	/*	polygon->Init("",250,400,0,0);
		m_pSelectSongFrame.push_back(polygon);
		polygon->UnInit();*/

	Thumbnail::Init(url[songNumber]);
}
