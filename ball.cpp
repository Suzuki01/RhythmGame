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
	//ƒNƒH[ƒ^ƒjƒIƒ“‚Ì‰Šú‰»
	m_Quaternion = XMQuaternionIdentity();
	m_Transform.Scale = { 0.01f,0.01f,0.01f };
	m_pModelAnimation = new ModelAnimation;
	m_pModelAnimation->Load(fileName);
}

void Ball::Update() {

	if (Input::Keyboard_IsPress('A')) {
		//‰ñ“]Ž²Œˆ’è
		XMFLOAT3 vz = XMFLOAT3(0.0f, 0.0f, 1.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);

		//Ž²‰ñ“]
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, 0.2f);
		
		//Quaternion’Ê‚µ‚ÌŠ|‚¯ŽZ
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);
		m_Transform.Position.x -= 0.1f;
		//³‹K‰»‚·‚éi™X‚ÉŒë·‚ªo‚Ä‚µ‚Ü‚¤‚½‚ßj
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
	}
	if (Input::Keyboard_IsPress('D')) {
		//‰ñ“]Ž²Œˆ’è
		XMFLOAT3 vz = XMFLOAT3(0.0f, 0.0f, 1.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		m_Transform.Position.x += 0.1f;

		//Ž²‰ñ“]
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, -0.2f);

		//Quaternion’Ê‚µ‚ÌŠ|‚¯ŽZ
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);

		//³‹K‰»‚·‚éi™X‚ÉŒë·‚ªo‚Ä‚µ‚Ü‚¤‚½‚ßj
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
	}
	if (Input::Keyboard_IsPress('W')) {
		//‰ñ“]Ž²Œˆ’è
		XMFLOAT3 vz = XMFLOAT3(1.0f, 0.0f, 0.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		m_Transform.Position.z += 0.1f;
		//Ž²‰ñ“]
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, 0.2f);

		//Quaternion’Ê‚µ‚ÌŠ|‚¯ŽZ
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);

		//³‹K‰»‚·‚éi™X‚ÉŒë·‚ªo‚Ä‚µ‚Ü‚¤‚½‚ßj
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
	}
	if (Input::Keyboard_IsPress('S')) {
		//‰ñ“]Ž²Œˆ’è
		XMFLOAT3 vz = XMFLOAT3(1.0f, 0.0f, 0.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		m_Transform.Position.z -= 0.1f;
		//Ž²‰ñ“]
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, -0.2f);

		//Quaternion’Ê‚µ‚ÌŠ|‚¯ŽZ
		m_Quaternion = XMQuaternionMultiply(m_Quaternion, rotation);

		//³‹K‰»‚·‚éi™X‚ÉŒë·‚ªo‚Ä‚µ‚Ü‚¤‚½‚ßj
		m_Quaternion = XMQuaternionNormalize(m_Quaternion);
	}

}

void Ball::Draw() {
	//‚µ‚·‚¢‚¾ƒJƒŠƒ“ƒO
	CCamera* camera;
	camera = CManager::GetScene()->GetComponent<CCamera>(Scene::CameraLayer);
	if (camera->GetVisibility(m_Transform.Position) == false)
		return;
		
	XMMATRIX world;
	world = XMMatrixScaling(m_Transform.Scale.x, m_Transform.Scale.y, m_Transform.Scale.z);
	world *= XMMatrixRotationQuaternion(m_Quaternion); //ƒNƒH[ƒ^ƒjƒIƒ“¨ƒ}ƒgƒŠƒNƒX
	world *= XMMatrixTranslation(m_Transform.Position.x, m_Transform.Position.y, m_Transform.Position.z);
	m_pModelAnimation->Draw(world);
}
