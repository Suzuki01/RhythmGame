#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "game_object.h"
#include "polygon.h"

void CPolygon::Init() {
	//���_�z��̍쐬
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(50.0f, 50.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(100, 50.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(50.0f, 100.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(100.0f, 100.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	//���_�o�b�t�@�쐬
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4; //*4
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	
	//�e�N�X�`���ǂݍ���
	m_Texture = new CTexture();
	m_Texture->Load("asset/number.tga");
}

void CPolygon::Uninit(){
	m_VertexBuffer->Release();
	m_Texture->Unload();
	delete m_Texture;
}

void CPolygon::Draw() {
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset); //���_�o�b�t�@�ݒ�@��x�ɕ����̒��_��ݒ�ł���
	CRenderer::SetTexture(m_Texture);    //�e�N�X�`���ݒ�
	CRenderer::SetWorldViewProjection2D(); //2D�}�g���N�X�ݒ�
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //�g�|���W�[�ݒ�i���_���ǂ�����Č��Ԃ��j
	CRenderer::GetDeviceContext()->Draw(4, 0);//�|���S���`��
}

void CPolygon::Update() {

}