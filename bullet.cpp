#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "game_object.h"
#include "model.h"
#include "bill_board.h"
#include "enemy.h"
#include "scene.h"
#include "bullet.h"

typedef struct {
}BulletData;

Bullet::Bullet() {
	m_Transform.Position = XMFLOAT3(0, 1.0f, 0);
	m_Transform.Scale = XMFLOAT3(2.0f, 4.0f, 2.0f);
	m_Transform.Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_BillBoard = new BillBoard();
	m_BillBoard->Init();
}

Bullet::~Bullet() {
	m_BillBoard->UnInit();
	delete m_BillBoard;
}

void Bullet::Init() {
}

void Bullet::Update() {
	if (m_Transform.Position.z > 10.0f) {
		CManager::GetScene()->DestroyGameObject(this);
	}
	m_Transform.Position.z += 0.1f;
	m_BillBoard->m_Transform = m_Transform;

	Up();
}

void Bullet::Draw() {
	m_BillBoard->Draw();
}

void Bullet::Create() {
	
}

void Bullet::UnInit() {
}

void Bullet::SetPosition(XMFLOAT3 position) {
	m_Transform.Position = position;
}

void Bullet::Up() {
	std::vector<Enemy*> enemys;
	enemys = CManager::GetScene()->GetComponents<Enemy>(3);
	for (Enemy* enemy : enemys) {
		if (enemy != nullptr) {
			XMFLOAT3 enemyPos = enemy->m_Transform.GetPosition();
			if (enemyPos.x - 1 <= this->m_Transform.Position.x && enemyPos.x + 1 >= this->m_Transform.Position.x && enemyPos.z <= this->m_Transform.Position.z) {//Õ“Ë”»’è
				CManager::GetScene()->DestroyGameObject(enemy);
				CManager::GetScene()->DestroyGameObject(this);
				return;
			}
		}
	}
}
