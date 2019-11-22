#include "main.h"
#include "renderer.h"
#include "game_object.h"
#include "manager.h"
#include "input.h"
#include "polygon.h"
#include "scene.h"
#include "audio_clip.h"
#include "notes.h"
#include "sound_manager.h"
#include "song_selection_scene.h"
#include "game_scene.h"
#include "test_scene.h"
#include "editor_scene.h"
#include "title_scene.h"

void TitleScene::Init()
{
	AddGameObject<CPolygon>(0)->Init("asset/background.png",0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	AddGameObject<CPolygon>(0)->Init("asset/title.png",330,100,397,84);
	AddGameObject<CPolygon>(0)->Init("asset/press_to_space.png",330,450,397,84);
	//m_SE = new CAudioClip;
}

void TitleScene::UnInit()
{
	Scene::UnInit();
}

void TitleScene::Update()
{
	Scene::Update();

	if (Input::Keyboard_IsTrigger(VK_SPACE)) {
		Notes::isEditorMode = false;
		CManager::SetScene<SongSelectionScene>();
	}
	if (Input::Keyboard_IsTrigger(VK_RETURN)) {
		CManager::SetScene<TestScene>();
	}
	if (Input::Keyboard_IsTrigger('E')) {
		Notes::isEditorMode = true;
		CManager::SetScene<SongSelectionScene>();
//		CManager::SetScene<EditorScene>();
	}
	if (Input::Keyboard_IsTrigger(VK_MBUTTON)) {
		CManager::SetScene<EditorScene>();
	}
}

void TitleScene::Draw() {
	Scene::Draw();
}