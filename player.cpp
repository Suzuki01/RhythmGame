#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "game_object.h"
#include "camera.h"
#include "texture.h"
#include "model.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "field.h"
#include "mesh_field.h"
#include "polygon.h"
#include "scene.h"


void Player::Init() {
	m_Transform.Position = XMFLOAT3(0, 1.0f, 0);
	m_Transform.Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Transform.Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);

	m_Model = new CModel();
	m_Model->Load("asset/miku_01.obj");
}

void Player::Update() {
	//上
	if (Input::Keyboard_IsPress('W')) {
		m_Transform.Position.z += 0.1f;
	}
	//下
	if (Input::Keyboard_IsPress('S')) {
		m_Transform.Position.z -= 0.1f;
	}
	//左
	if (Input::Keyboard_IsPress('A')) {
		m_Transform.Position.x -= 0.1f;
	}
	//右
	if (Input::Keyboard_IsPress('D')) {
		m_Transform.Position.x += 0.1f;
	}

	if (Input::Keyboard_IsTrigger('P')) {
		Scene* scene = CManager::GetScene();
		Bullet* bullet = scene->AddGameObject<Bullet>(5);
		bullet->SetPosition(m_Transform.Position);
	}

	if (Input::Keyboard_IsTrigger('E')) {
		Scene* scene = CManager::GetScene();
		Enemy* enemy = scene->AddGameObject<Enemy>(3);
		enemy->SetPosition(m_Transform.Position);
	}
}

void Player::Draw() {
	// マトリクス設定
	m_Transform.SetWorldMatrix();
	m_Model->Draw();
}

void Player::UnInit() {
	m_Model->Unload();
	delete m_Model;
}
