#include "main.h"
#include "renderer.h"
#include "game_object.h"
#include "manager.h"
#include "input.h"
#include "scene.h"
#include "game_scene.h"
#include "polygon.h"
#include "audio_clip.h"
#include "sound_manager.h"
#include "title_scene.h"

void TitleScene::Init()
{
	AddGameObject<CPolygon>(0)->Init();
	m_SE = new CAudioClip;

}

void TitleScene::UnInit()
{
	Scene::UnInit();
}

void TitleScene::Update()
{

	Scene::Update();

	if (Input::Keyboard_IsTrigger(VK_RETURN)) {
		CManager::SetScene<GameScene>();
	}
}
