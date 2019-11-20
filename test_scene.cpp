#include "main.h"
#include "scene.h"
#include "camera.h"
#include "player.h"
#include "ball.h"
#include "mesh_field.h"
#include "model.h"
#include "test_scene.h"

CModel* g_model;

void TestScene::Init()
{
	g_model = new CModel;
	g_model->Load("asset/model/miku_01.obj");
	AddGameObject<CCamera>(CameraLayer)->Init();
//	AddGameObject<Player>(PlayerLayer)->Init();
//	AddGameObject<Ball>(PlayerLayer)->Init("asset/miku_01.obj");
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
	g_model->Draw();
	Scene::Draw();
}