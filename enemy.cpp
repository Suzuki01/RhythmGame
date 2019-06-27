#include "main.h"
#include "game_object.h"
#include "model.h"
#include "input.h"
#include "enemy.h"

Enemy::Enemy() {
	m_Transform.Position = XMFLOAT3(2.0f, 1.0f, 0);
	m_Transform.Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Transform.Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);

	m_Model = new CModel();
	m_Model->Load("asset/miku_01.obj");
}

Enemy::~Enemy() {

}

void Enemy::Init() {
	m_Transform.Position = XMFLOAT3(2.0f, 1.0f, 0);
	m_Transform.Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_Transform.Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);

	m_Model = new CModel();
	m_Model->Load("asset/miku_01.obj");
}

void Enemy::Update() {
	//上
	if (Input::Keyboard_IsPress('U')) {
		m_Transform.Position.z += 0.1f;
	}
	//下
	if (Input::Keyboard_IsPress('J')) {
		m_Transform.Position.z -= 0.1f;
	}
	//左
	if (Input::Keyboard_IsPress('H')) {
		m_Transform.Position.x -= 0.1f;
	}
	//右
	if (Input::Keyboard_IsPress('K')) {
		m_Transform.Position.x += 0.1f;
	}
}

void Enemy::Draw() {
	// マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling(m_Transform.Scale.x, m_Transform.Scale.y, m_Transform.Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Transform.Rotation.x, m_Transform.Rotation.y, m_Transform.Rotation.z);
	world *= XMMatrixTranslation(m_Transform.Position.x, m_Transform.Position.y, m_Transform.Position.z);
	CRenderer::SetWorldMatrix(&world);

	m_Model->Draw();
}

void Enemy::UnInit() {
	m_Model->Unload();
	delete m_Model;
}

void Enemy::SetPosition(XMFLOAT3 position) {
	m_Transform.Position = position;
	m_Transform.Position.z += 3.0f;
}
