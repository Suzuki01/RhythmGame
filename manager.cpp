#include <list>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "game_object.h"
#include "mesh_field.h"
#include "field.h"
#include "polygon.h"
#include "texture.h"
#include "player.h"
#include "enemy.h"
#include "input.h"
#include "scene.h"

Scene* g_Scene;

void CManager::Init()
{
	CRenderer::Init();
	Input::Init();
	//CTexture::TextureLoad();
	g_Scene = new Scene();
	g_Scene->Init();
	
}

void CManager::Uninit()
{
	g_Scene->UnInit();
	delete g_Scene;
	//Input::UnInit(); ‚Ü‚¾ì‚Á‚Ä‚¢‚È‚¢
	CRenderer::Uninit();

}

void CManager::Update()
{
	Input::Update();
	g_Scene->Update();
}

void CManager::Draw()
{

	CRenderer::Begin();
	g_Scene->Draw();
	CRenderer::End();

}

Scene* CManager::GetScene() {
	return g_Scene;
}
