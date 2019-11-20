#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "game_object.h"
#include "camera.h"
#include "input.h"
#include "model_animation.h"
#include "scene.h"
#include "ball.h"


void Ball::Init(char* fileName) {
	//クォータニオンの初期化
	m_Quaternion = XMQuaternionIdentity();
	m_Transform.Scale = { 0.01f,0.01f,0.01f };
	m_pModelAnimation = new ModelAnimation;
	m_pModelAnimation->Load(fileName);
}

void Ball::Update() {

	if (Input::Keyboard_IsPress('A')) {
		//回転軸決定
		XMFLOAT3 vz = XMFLOAT3(0.0f, 0.0f, 1.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);

		//軸回転
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, 0.2f);
		
		//Quaternion通しの掛け算
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);
		m_Transform.Position.x -= 0.1f;
		//正規化する（徐々に誤差が出てしまうため）
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
	}
	if (Input::Keyboard_IsPress('D')) {
		//回転軸決定
		XMFLOAT3 vz = XMFLOAT3(0.0f, 0.0f, 1.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		m_Transform.Position.x += 0.1f;

		//軸回転
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, -0.2f);

		//Quaternion通しの掛け算
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);

		//正規化する（徐々に誤差が出てしまうため）
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
	}
	if (Input::Keyboard_IsPress('W')) {
		//回転軸決定
		XMFLOAT3 vz = XMFLOAT3(1.0f, 0.0f, 0.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		m_Transform.Position.z += 0.1f;
		//軸回転
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, 0.2f);

		//Quaternion通しの掛け算
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);

		//正規化する（徐々に誤差が出てしまうため）
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
	}
	if (Input::Keyboard_IsPress('S')) {
		//回転軸決定
		XMFLOAT3 vz = XMFLOAT3(1.0f, 0.0f, 0.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		m_Transform.Position.z -= 0.1f;
		//軸回転
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, -0.2f);

		//Quaternion通しの掛け算
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);

		//正規化する（徐々に誤差が出てしまうため）
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
	}

}

void Ball::Draw() {
	//しすいだカリング
	CCamera* camera;
	camera = CManager::GetScene()->GetComponent<CCamera>(Scene::CameraLayer);
	if (camera->GetVisibility(m_Transform.Position) == false)
		return;
		
	XMMATRIX world;
	world = XMMatrixScaling(m_Transform.Scale.x, m_Transform.Scale.y, m_Transform.Scale.z);
	world *= XMMatrixRotationQuaternion(m_Quaternion); //クォータニオン→マトリクス
	world *= XMMatrixTranslation(m_Transform.Position.x, m_Transform.Position.y, m_Transform.Position.z);
	m_pModelAnimation->Draw(world);
}
