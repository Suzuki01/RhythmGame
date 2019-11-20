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
	//�N�H�[�^�j�I���̏�����
	m_Quaternion = XMQuaternionIdentity();
	m_Transform.Scale = { 0.01f,0.01f,0.01f };
	m_pModelAnimation = new ModelAnimation;
	m_pModelAnimation->Load(fileName);
}

void Ball::Update() {

	if (Input::Keyboard_IsPress('A')) {
		//��]������
		XMFLOAT3 vz = XMFLOAT3(0.0f, 0.0f, 1.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);

		//����]
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, 0.2f);
		
		//Quaternion�ʂ��̊|���Z
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);
		m_Transform.Position.x -= 0.1f;
		//���K������i���X�Ɍ덷���o�Ă��܂����߁j
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
	}
	if (Input::Keyboard_IsPress('D')) {
		//��]������
		XMFLOAT3 vz = XMFLOAT3(0.0f, 0.0f, 1.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		m_Transform.Position.x += 0.1f;

		//����]
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, -0.2f);

		//Quaternion�ʂ��̊|���Z
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);

		//���K������i���X�Ɍ덷���o�Ă��܂����߁j
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
	}
	if (Input::Keyboard_IsPress('W')) {
		//��]������
		XMFLOAT3 vz = XMFLOAT3(1.0f, 0.0f, 0.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		m_Transform.Position.z += 0.1f;
		//����]
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, 0.2f);

		//Quaternion�ʂ��̊|���Z
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);

		//���K������i���X�Ɍ덷���o�Ă��܂����߁j
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
	}
	if (Input::Keyboard_IsPress('S')) {
		//��]������
		XMFLOAT3 vz = XMFLOAT3(1.0f, 0.0f, 0.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		m_Transform.Position.z -= 0.1f;
		//����]
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, -0.2f);

		//Quaternion�ʂ��̊|���Z
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);

		//���K������i���X�Ɍ덷���o�Ă��܂����߁j
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
	}

}

void Ball::Draw() {
	//���������J�����O
	CCamera* camera;
	camera = CManager::GetScene()->GetComponent<CCamera>(Scene::CameraLayer);
	if (camera->GetVisibility(m_Transform.Position) == false)
		return;
		
	XMMATRIX world;
	world = XMMatrixScaling(m_Transform.Scale.x, m_Transform.Scale.y, m_Transform.Scale.z);
	world *= XMMatrixRotationQuaternion(m_Quaternion); //�N�H�[�^�j�I�����}�g���N�X
	world *= XMMatrixTranslation(m_Transform.Position.x, m_Transform.Position.y, m_Transform.Position.z);
	m_pModelAnimation->Draw(world);
}
