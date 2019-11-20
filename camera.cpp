#include "main.h"
#include "renderer.h"
#include "transform.h"
#include "game_object.h"
#include "input.h"
#include "camera.h"

bool move;

void CCamera::Init()
{
	m_Transform.Position = XMFLOAT3( 0.0f, 12.0f, -20.0f );
	m_Transform.Rotation = XMFLOAT3( 0.5f, 0.0f, 0.0f );
	m_Viewport.left = 0;
	m_Viewport.top = 0;
	m_Viewport.right = SCREEN_WIDTH;
	m_Viewport.bottom = SCREEN_HEIGHT;

	rollTime = 0;
}


void CCamera::Uninit()
{
}


void CCamera::Update()
{
/*	//上
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
	if (Input::Keyboard_IsPress('R')) {
		m_Transform.Position.y += 0.1f;
	}
	if (Input::Keyboard_IsPress('F')) {
		m_Transform.Position.y -= 0.1f;
	}
	if (Input::Keyboard_IsPress('J')) {
		m_Transform.Rotation.y += 0.05f;
	}
	if (Input::Keyboard_IsPress('L')) {
		m_Transform.Rotation.y -= 0.05f;
	}
	if (Input::Keyboard_IsPress('I')) {
		m_Transform.Rotation.x -= 0.05f;
	}
	if (Input::Keyboard_IsPress('K')) {
		m_Transform.Rotation.x += 0.05f;
	}
	if (Input::Keyboard_IsPress('Y')) {
		m_Transform.Rotation.z += 0.05f;
	}
	if (Input::Keyboard_IsPress('H')) {
		m_Transform.Rotation.z -= 0.05f;
	}
	
	if (Input::Keyboard_IsTrigger(VK_RETURN)) {
//		isRoll = true;
	}
	if(isRoll)
		Roll(2, true, false, false);*/
	m_Transform.Quaternion.EulerToQuaternion(m_Transform.Rotation.x, m_Transform.Rotation.y, m_Transform.Rotation.z);
}



void CCamera::Draw()
{

	// ビューポート設定
	D3D11_VIEWPORT dxViewport;
	dxViewport.Width = (float)(m_Viewport.right - m_Viewport.left);
	dxViewport.Height = (float)(m_Viewport.bottom - m_Viewport.top);
	dxViewport.MinDepth = 0.0f;
	dxViewport.MaxDepth = 1.0f;
	dxViewport.TopLeftX = (float)m_Viewport.left;
	dxViewport.TopLeftY = (float)m_Viewport.top;

	CRenderer::GetDeviceContext()->RSSetViewports(1, &dxViewport);

	// ビューマトリクス設定
	m_InvViewMatrix = m_Transform.Quaternion.QuaternionToRotationMatrix();
//	m_InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Transform.Rotation.x, m_Transform.Rotation.y, m_Transform.Rotation.z);
	m_InvViewMatrix *= XMMatrixTranslation(m_Transform.Position.x, m_Transform.Position.y, m_Transform.Position.z);

	XMVECTOR det;
	m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);

	CRenderer::SetViewMatrix(&m_ViewMatrix);

	// プロジェクションマトリクス設定
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, dxViewport.Width / dxViewport.Height, 1.0f, 1000.0f);

	CRenderer::SetProjectionMatrix(&m_ProjectionMatrix);
}

XMMATRIX CCamera::GetViewMatrix() {
	return m_ViewMatrix;
}

XMMATRIX CCamera::GetProjectMatrix()
{
	return m_ProjectionMatrix;
}

XMMATRIX CCamera::GetWorldMatrix() {
	return m_InvViewMatrix;
}

void CCamera::Roll(float time,bool x,bool y,bool z) {
	rotationAmount = 6.5;
	if (time > rollTime) {
		if (x) {
			m_Transform.Rotation.x += rotationAmount;
		}
		else if (y) {
			m_Transform.Rotation.y += rotationAmount;
		}
		else if (z) {
			m_Transform.Rotation.z += rotationAmount;
		}
		rollTime++;
	}
	else {
		rollTime = 0;
		isRoll = false;
	}
}

bool CCamera::GetVisibility(XMFLOAT3 position)
{
	XMVECTOR worldPos, viewPos, projPos;
	worldPos = {0};
	XMFLOAT3 projPosF;
	worldPos = XMLoadFloat3(&position);
	viewPos = XMVector3TransformCoord(worldPos,m_ViewMatrix);
	projPos = XMVector3TransformCoord(viewPos,m_ProjectionMatrix);
	XMStoreFloat3(&projPosF,projPos);

	if (-1.0f < projPosF.x && projPosF.x < 1.0f && -1.0f < projPosF.y && projPosF.y < 1.0f && 0.0f < projPosF.z && projPosF.z < 1.0f) {
		return true;
	}
	return false;
}
