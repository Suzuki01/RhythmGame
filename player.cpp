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
#include "model_animation.h"

int fr;
float blend;
void Player::Init(XMFLOAT3 pos) {
	m_Transform.Position = pos;
	m_Transform.Scale = XMFLOAT3(0.0001f, 0.0001f, 0.0001f);
	m_Transform.Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);

	m_pModel = new ModelAnimation();
//	m_pModel->Load("asset/model/ball.fbx");	
	m_pModel->Load("asset/model/human_walk.fbx");	
//	m_pModel->Load("asset/model/testex.fbx");	
//	m_pModel->Load("asset/model/mixamo/SambaDancing2.fbx");	
	fr = 0;
	blend = 0;
}

void Player::Update() {
	//上
	if (Input::Keyboard_IsPress('W')) {
		m_Transform.Position.z += 0.1f;
		m_pModel->SetAnimation(0);
		fr++;
	}
	//下
	if (Input::Keyboard_IsPress('S')) {
		m_Transform.Position.z -= 0.1f;
		m_pModel->SetAnimation(0);
		fr++;
	}
	//左
	if (Input::Keyboard_IsPress('A')) {
		m_Transform.Position.x -= 0.1f;
		m_pModel->SetAnimation(0);
		fr++;
	}
	//右
	if (Input::Keyboard_IsPress('D')) {
		m_Transform.Position.x += 0.1f;
		m_pModel->SetAnimation(0);
		fr++;
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
	if (Input::Keyboard_IsTrigger(VK_RETURN)) {
		//jump
		fr = 0;
		m_pModel->SetAnimation(1);
	}
	if (m_pModel->GetAnimationID() == 1) {
		Jump();
	}
	m_pModel->Update(m_pModel->GetAnimationID(),1,blend, fr);
	matrix = XMMatrixScaling(1, 1, 1);
	XMVECTOR vec = {0.0f,1.0f,0.0f };
	matrix *= XMMatrixRotationAxis(vec,3.0f);
	matrix *= XMMatrixTranslation(m_Transform.Position.x, m_Transform.Position.y, m_Transform.Position.z);
	MeshField* field = CManager::GetScene()->GetComponent<MeshField>(1);
//	m_Transform.Position.y = field->GetHeight(m_Transform.Position) + 1.0f;
//	fr++;
	blend += 0.1f;
}
float t = 0;
void Player::Draw() {
	// マトリクス設定
//	m_Transform.SetWorldMatrix();
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
	m_pModel->Draw(matrix);
	//m_Model->Draw(CRenderer::GetDeviceContext());
}

void Player::UnInit() {
	m_pModel->Unload();
	delete m_pModel;
}

void Player::Jump() {
	if (fr < 50) {
		m_Transform.Position.y += 0.2;
	}
	else if(fr < 100) {
		m_Transform.Position.y -= 0.2;
	}

	if (fr > 120) {
		m_pModel->SetAnimation(0);
		fr = 0;
	}
	fr++;
}