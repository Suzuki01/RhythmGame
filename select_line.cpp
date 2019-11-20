#include "main.h"
#include "renderer.h"
#include "game_object.h"
#include "bill_board.h"
#include "texture.h"
#include "texture_manager.h"
#include "input.h"
#include "select_line.h"

void SelectLine::RaneLimitation()
{
	if (m_RaneNumber > m_MaxRane) {
		m_RaneNumber = m_MaxRane;
	}
	else if (m_RaneNumber < 1) {
		m_RaneNumber = 1;
	}
}

void SelectLine::Init(char* fileName, XMFLOAT3 startPos, float verticalSize, float horizontalSize, int maxRane, float moveAmount)
{
	VERTEX_3D v[] = {
		{XMFLOAT3(-0.5f,0.0f, 0.5f),XMFLOAT3(0.0f,1.0f,0.0f),XMFLOAT4(1.0f,1.0f,1.0f,1.0f),XMFLOAT2(0.0f,0.0f)},
		{XMFLOAT3(0.5f,0.0f, 0.5f),XMFLOAT3(0.0f,1.0f,0.0f),XMFLOAT4(1.0f,1.0f,1.0f,1.0f),XMFLOAT2(1.0f,0.0f)},
		{XMFLOAT3(-0.5f,0.0f,-0.5f),XMFLOAT3(0.0f,1.0f,0.0f),XMFLOAT4(1.0f,1.0f,1.0f,1.0f),XMFLOAT2(0.0f,1.0f)},
		{XMFLOAT3(0.5f,0.0f,-0.5f),XMFLOAT3(0.0f,1.0f,0.0f),XMFLOAT4(1.0f,1.0f,1.0f,1.0f),XMFLOAT2(1.0f,1.0f)},
	};

	//���_�o�b�t�@�쐬
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4; //*4
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = v;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//�e�N�X�`���ǂݍ���
	m_Texture = new CTexture();
	m_Texture = TextureManager::Load(fileName);


	m_MaxRane = maxRane;
	m_MoveAmount = moveAmount;
	m_RaneNumber = 1;
//	m_Transform.Position.x = 10;

	m_Billboard = new BillBoard();
	m_Billboard->Init("asset/jo.png");
	m_Billboard->m_Transform.Position.z = 4;
	m_Billboard->m_Transform.Position = startPos;
//	m_Billboard->m_Transform.Scale = XMFLOAT3(verticalSize,0.0f,horizontalSize);
}

void SelectLine::Update()
{
	if (Input::Keyboard_IsPress('W')) {
		m_Billboard->m_Transform.Position.z += 1.0f;
		if (m_Billboard->m_Transform.Position.z > 30) {
			m_Billboard->m_Transform.Position.z = 30.0f;
		}
	}
	if (Input::Keyboard_IsPress('S')) {
		m_Billboard->m_Transform.Position.z -= 1.0f;
		if (m_Billboard->m_Transform.Position.z < 2) {
			m_Billboard->m_Transform.Position.z = 2.0f;
		}
	}
	if (Input::Keyboard_IsTrigger('D')) {
		if (m_RaneNumber != m_MaxRane) {
			m_Billboard->m_Transform.Position.x += m_MoveAmount;
			m_RaneNumber++;
			RaneLimitation();
		}
	}
	if (Input::Keyboard_IsTrigger('A')) {
		if (m_RaneNumber != 1) {
			m_Billboard->m_Transform.Position.x -= m_MoveAmount;
			m_RaneNumber--;
			RaneLimitation();
		}
	}


}

void SelectLine::UnInit()
{

}

void SelectLine::Draw() {
	// �e�N�X�`���ݒ�
	CRenderer::SetTexture(m_Texture);
	// ���_�o�b�t�@�ݒ�
	CRenderer::SetVertexBuffers(m_VertexBuffer);

	m_Transform.SetBillBoardWorldMatrix();
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //�g�|���W�[�ݒ�i���_���ǂ�����Č��Ԃ��j
	CRenderer::GetDeviceContext()->Draw(4, 0);//�|���S���`��
	m_Billboard->Draw();
}

