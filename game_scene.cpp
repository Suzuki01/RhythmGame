#include "main.h"
#include "renderer.h"
#include "game_object.h"
#include "mesh_field.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "notes.h"
#include "audio_clip.h"
#include "sound_manager.h"
#include "scene.h"
#include "result_scene.h"
#include "manager.h"
#include "game_scene.h"

void GameScene::Init() {
	//AddGameObject<CPolygon>(7)->Init();
	AddGameObject<CCamera>(CameraLayer)->Init();
	AddGameObject<MeshField>(FieldLayer)->Init(10, 10, 25, 5, 5);
	AddGameObject<Player>(PlayerLayer)->Init();
	m_pBGM = new CAudioClip;
	m_pBGM = SoundManager::Load("asset/sound/FIRE-GROUND.wav");//wavのみ
	m_pBGM->Play(false);
}

void GameScene::UnInit() {
	m_pBGM->Stop();
	Scene::UnInit(); //継承元の呼び出しなのでstaticメソッドの呼び出しではない
}

void GameScene::Update() {
	Scene::Update();

	if (Input::Keyboard_IsTrigger(VK_RETURN)) {
		CManager::SetScene<ResultScene>();
	}
}