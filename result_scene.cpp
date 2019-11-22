#include "result_scene.h"

void ResultScene::Init()
{
	XMFLOAT3 position = {350,SCREEN_HEIGHT * 0.3f,0.0f};
	//Score::SetPosition(position);
	AddGameObject<CPolygon>(0)->Init("asset/background.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	AddGameObject<CPolygon>(0)->Init("asset/result.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	AddGameObject<CPolygon>(0)->Init("asset/result_ui.png", 200, 250, 135, 260);
	AddGameObject<CPolygon>(0)->Init("asset/title_result.png", 400, 0, 377, 168);
}

void ResultScene::UnInit()
{

}

void ResultScene::Update()
{
	//Scene::Update();

	if (Input::Keyboard_IsTrigger(VK_SPACE)) {
		CManager::SetScene<TitleScene>();
	}
}

void ResultScene::Draw() {
	Scene::Draw();
	Score::ResultDraw();
	Thumbnail::Draw();
//	m_pPolygon->Draw();
}