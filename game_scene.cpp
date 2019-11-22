#include "main.h"
#include "renderer.h"
#include "game_object.h"
#include "field.h"
#include "mesh_field.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "notes.h"
#include "polygon.h"
#include "bill_board.h"
#include "sound.h"
#include "audio_clip.h"
#include "sound_manager.h"
#include "scene.h"
#include "result_scene.h"
#include "manager.h"
#include "notes.h"
#include "thumbnail.h"
#include "mesh_sky.h"
#include "score.h"
#include "game_scene.h"


void GameScene::Init() {
	AddGameObject<CCamera>(CameraLayer)->Init();
//	AddGameObject<Player>(PlayerLayer)->Init();
	AddGameObject<MeshField>(FieldLayer)->Init(4, 16, 100, 5, 20);
	AddGameObject<Field>(JusticeFieldLayer)->Init();
//	AddGameObject<MeshSky>(SkyDomeLayer)->Init(1.5,42,40,40);

	Notes::Init();
	Score::Init(5);
	count = 0;
	m_Phase = PHASE_INDEX_READY;
	ready = new CPolygon;
	ready->Init("asset/ready.png",0,0,SCREEN_WIDTH,168);
	ready->m_Transform.Position = { -SCREEN_WIDTH, SCREEN_HEIGHT * 0.5f -100,0 };
	go = new CPolygon;
	go->Init("asset/start.png",0.0f, 0.0f, SCREEN_WIDTH, 168);
	go->m_Transform.Position = { 0.0f, SCREEN_HEIGHT * 0.5f- 100,0 };
}

void GameScene::UnInit() {
//	m_pBGM->Stop();
	Sound::UnInit();
	Notes::UnInit();
	Scene::UnInit(); //継承元の呼び出しなのでstaticメソッドの呼び出しではない
}

void GameScene::Update() {
	Scene::Update();

	switch (m_Phase) {
	case PHASE_INDEX_READY:
		if (ready->m_Transform.Position.x >= 0.0f) {
			ready->m_Transform.Position.x = 0.0f;
			if (count >= 120) {
				m_Phase = PHASE_INDEX_GO;
				count = 0;
			}
			else {
				count++;
			}
		}
		else {
			ready->m_Transform.Position.x += 20;
		}
		break;
	case PHASE_INDEX_GO:
		if (go->m_Transform.Position.x >= SCREEN_WIDTH) {
			if (count >= 60) {
				m_Phase = PHASE_INDEX_START;
				Sound::Start();
				count = 0;
			}
		}
		else if(count >= 120) {
			go->m_Transform.Position.x += 20.0f;
		}
		else {
			count++;
		}
		break;
	case PHASE_INDEX_START:
		Notes::Update();
		if (Input::Keyboard_IsTrigger(VK_SPACE)) {
			CManager::SetScene<ResultScene>();
		}
		if (Input::Keyboard_IsTrigger('K')) {
		}

		if (Notes::EndCheck()) {
			CManager::SetScene<ResultScene>();
		}
	}
}

void GameScene::Draw() {

	Scene::Draw();
	Notes::Draw();
	Score::Draw();
	Thumbnail::Draw();
	switch (m_Phase) {
	case PHASE_INDEX_READY:
		ready->Draw();
		break;
	case PHASE_INDEX_GO:
		go->Draw();
		break;
	default:
		break;
	}
}