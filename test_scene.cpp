#include "main.h"
#include "scene.h"
#include "camera.h"
#include "player.h"
#include "mesh_field.h"
#include "test_scene.h"

void TestScene::Init()
{
	AddGameObject<CCamera>(CameraLayer)->Init();
	AddGameObject<Player>(PlayerLayer)->Init();
	AddGameObject<MeshField>(FieldLayer)->Init(20, 20, 25, 5, 5);
}

void TestScene::Update()
{
	Scene::Update();
}

void TestScene::UnInit()
{
	 
}

void TestScene::Draw() {
	Scene::Draw();
}