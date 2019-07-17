#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "title_scene.h"
#include "input.h"
#include "manager.h"
#include "result_scene.h"

void ResultScene::Init()
{

}

void ResultScene::UnInit()
{
}

void ResultScene::Update()
{
	//Scene::Update();

	if (Input::Keyboard_IsTrigger(VK_RETURN)) {
		CManager::SetScene<TitleScene>();
	}
}
