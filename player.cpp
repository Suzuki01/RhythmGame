#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "game_object.h"
#include "camera.h"
#include "texture.h"
#include "model.h"
#include "input.h"
#include "mesh_field.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "scene.h"


void Player::Init() {
	m_Transform.Position = XMFLOAT3(0, 1.0f, 0);
	m_Transform.Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Transform.Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);

	m_Model = new CModel();
	m_Model->Load("asset/miku_01.obj");
//	m_Model->Load(CRenderer::GetDevice(), CRenderer::GetDeviceContext(), "asset/model/miku_01.obj");
	
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
	//m_Transform.Rotation.y += 0.1;
	MeshField* field = CManager::GetScene()->GetComponent<MeshField>(1);
	m_Transform.Position.y = field->GetHeight(m_Transform.Position);
	
}
float t = 0;
void Player::Draw() {
	// マトリクス設定
	m_Transform.SetWorldMatrix();
	std::vector<Enemy*> enemys;
	enemys = CManager::GetScene()->GetComponents<Enemy>(3);
	if (t < 1) {
		t += 0.005;
	}
	else {
		t = 1;
	}
//	m_Transform.Quaternion.EulerToQuaternion(m_Transform.Position.x, m_Transform.Position.y, m_Transform.Position.z);
//	enemys[0]->m_Transform.Quaternion.EulerToQuaternion(enemys[0]->m_Transform.Position.x, enemys[0]->m_Transform.Position.y, enemys[0]->m_Transform.Position.z);
//	m_Transform.SetWorldLerpMatrix(m_Transform.Position,enemys[0]->m_Transform.GetPosition(),t);
//	m_Transform.Quaternion.EulerToQuaternion(m_Transform.Rotation.x, m_Transform.Rotation.y, m_Transform.Rotation.z);
//	m_Transform.SetWorldQuaternionMatrix();
	//m_Model->Draw();
	m_Model->Draw();
	//m_Model->Draw(CRenderer::GetDeviceContext());
}

void Player::UnInit() {
	m_Model->Unload();
	delete m_Model;
}
